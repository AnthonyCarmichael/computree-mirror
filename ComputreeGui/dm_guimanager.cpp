/****************************************************************************

 Copyright (C) 2010-2012 the Office National des Forêts (ONF), France
                     and the Association de Recherche Technologie et Sciences (ARTS), Ecole Nationale Suprieure d'Arts et Métiers (ENSAM), Cluny, France.
                     All rights reserved.

 Contact : alexandre.piboule@onf.fr

 Developers : MichaÃ«l KREBS (ARTS/ENSAM)

 This file is part of Computree version 2.0.

 Computree is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Computree is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Computree.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/


#include "dm_guimanager.h"

#include "view/MainView/gmainprogressdialog.h"

#include "ct_model/outModel/abstract/ct_outabstractitemmodel.h"
#include "ct_exporter/abstract/ct_abstractexporter.h"
#include "ct_itemdrawable/abstract/ct_abstractitemdrawable.h"
#include "ct_result/ct_resultgroup.h"

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtConcurrentRun>
#else
#include <QtConcurrent/QtConcurrentRun>
#endif

#include <QEventLoop>

DM_GuiManager* DM_GuiManager::_uniqueInstance = nullptr;

DM_GuiManager::~DM_GuiManager()
{
    qDeleteAll(_contextList.begin(), _contextList.end());
}

bool DM_GuiManager::isAsyncOperationInProgress() const
{
    return (m_currentAsyncOperation != nullptr);
}

DM_AsyncOperation* DM_GuiManager::requestExclusiveAsyncOperation(const DM_AbstractAsyncOperationOptions *options, bool wait)
{
    DM_AbstractAsyncOperationOptions *notConstOptions = (DM_AbstractAsyncOperationOptions*)options;
    DM_AbstractAsyncOperationOptions defaultOptions;

    if(notConstOptions == nullptr)
        notConstOptions = &defaultOptions;

    // mutex to protect the tokens list
    QMutexLocker locker(&m_asyncOperationTokenMutex);

    bool pass = notConstOptions->pass();

    if(!pass
        && !wait)
        return nullptr;

    bool canceled = false;

    DM_GuiManagerToken *token = new DM_GuiManagerToken(notConstOptions);
    m_tokens.append(token);

    if(!pass
        || (m_tokens.size() > 1))
    {
        QEventLoop event;

        do
        {
            DM_GuiManagerToken *lastToken = (m_tokens.size() == 1) ? nullptr : m_tokens.at(m_tokens.size()-2);

            if(lastToken != nullptr)
                connect(lastToken, SIGNAL(destroyed()), &event, SLOT(quit()), Qt::DirectConnection);
            else
                connect(token, SIGNAL(passed()), &event, SLOT(quit()), Qt::DirectConnection);

            locker.unlock();
            event.exec();
            locker.relock();

        }while(!notConstOptions->pass() || canceled);
    }

    if(!canceled)
    {
        GMainProgressDialog *pDialog = getMainWindow()->createWaitProgressDialog();

        pDialog->setWindowModality(Qt::WindowModal);
        pDialog->setCanClose(false);
        pDialog->setValue(0);
        pDialog->setLabelText("");
        pDialog->setSecondLabelText("");

        m_currentAsyncOperation = new DM_AsyncOperation();
        m_currentAsyncOperation->setProgressDialog(pDialog);

        pDialog->setData(m_currentAsyncOperation);

        connect(m_currentAsyncOperation, SIGNAL(destroyed()), this, SLOT(slotCurrentAsyncOperationDestroyed()), Qt::DirectConnection);
        connect(m_currentAsyncOperation, SIGNAL(destroyed()), this, SLOT(slotCurrentAsyncOperationReleased()), Qt::QueuedConnection);

        return m_currentAsyncOperation;
    }
    else
    {
        m_tokens.removeOne(token);
        delete token;
    }

    return nullptr;
}

bool DM_GuiManager::asyncAddAllItemDrawableOfResultOnView(CT_AbstractResult &res, DM_Context * /*context*/)
{
    if(!getStepManager()->isRunning()
            || !getStepManager()->getOptions().isAutoClearResultFromMemoryEnable())
    {
        /*DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

        if(aop != nullptr)
        {
            if(context != nullptr)
                connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

            ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                                 &res,
                                                                 nullptr,
                                                                 ".",
                                                                 getDocumentManagerView(),
                                                                 &_asyncProgress);

            initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant l'ajout du resultat au document actif."));

            _future = QtConcurrent::run(staticAddAllItemDrawableOfResultOnView, infoActionID);
            _futureWatcher.setFuture(_future);

            return true;
        }*/

        ActionItemDrawable infoActionID = ActionItemDrawable(nullptr,
                                                             &res,
                                                             nullptr,
                                                             ".",
                                                             getDocumentManagerView(),
                                                             &_asyncProgress);

        staticAddAllItemDrawableOfResultOnView(infoActionID);
    }

    return false;
}

bool DM_GuiManager::asyncAddAllItemDrawableOfModelOnView(CT_AbstractResult &res,
                                                         CT_OutAbstractItemModel &model,
                                                         DM_DocumentView &view,
                                                         DM_Context * /*context*/)
{
    if(model.result() == nullptr)
        return false;

    if((!getStepManager()->isRunning()
            || !getStepManager()->getOptions().isAutoClearResultFromMemoryEnable()))
    {
        /*DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

        if(aop != nullptr)
        {
            if(context != nullptr)
                connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

            ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                                 &res,
                                                                 nullptr,
                                                                 ".",
                                                                 getDocumentManagerView(),
                                                                 &_asyncProgress);
            infoActionID.setItemModel(&model);
            infoActionID.setDocumentView(&view);

            initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant l'ajout des items au document actif."));

            _future = QtConcurrent::run(staticAddAllItemDrawableOfModelOnView, infoActionID);
            _futureWatcher.setFuture(_future);

            return true;
        }*/

        ActionItemDrawable infoActionID = ActionItemDrawable(nullptr,
                                                             &res,
                                                             nullptr,
                                                             ".",
                                                             getDocumentManagerView(),
                                                             &_asyncProgress);
        infoActionID.setItemModel(&model);
        infoActionID.setDocumentView(&view);

        staticAddAllItemDrawableOfModelOnView(infoActionID);

        return true;
    }

    return false;
}

bool DM_GuiManager::asyncAddAllItemDrawableOfListOnView(QList<CT_AbstractItemDrawable*> &itemList, DM_DocumentView *view, DM_Context * /*context*/)
{
    if((!getStepManager()->isRunning()
            || !getStepManager()->getOptions().isAutoClearResultFromMemoryEnable()))
    {
        /*DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

        if(aop != nullptr)
        {
            if(context != nullptr)
                connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

            ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                                 nullptr,
                                                                 &itemList,
                                                                 ".",
                                                                 getDocumentManagerView(),
                                                                 &_asyncProgress);
            infoActionID.setDocumentView(view);

            initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant l'ajout des CT_AbstractItemDrawable au document actif."));

            _future = QtConcurrent::run(staticAddAllItemDrawableOfListOnView, infoActionID);
            _futureWatcher.setFuture(_future);

            return true;
        }*/

        ActionItemDrawable infoActionID = ActionItemDrawable(nullptr,
                                                             nullptr,
                                                             &itemList,
                                                             ".",
                                                             getDocumentManagerView(),
                                                             &_asyncProgress);
        infoActionID.setDocumentView(view);

        staticAddAllItemDrawableOfListOnView(infoActionID);

        return true;
    }

    return false;
}

bool DM_GuiManager::asyncRemoveAllItemDrawableOfResultFromView(CT_AbstractResult &res, DM_Context *context)
{
    DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

    if(aop != nullptr)
    {
        if(context != nullptr)
            connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

        ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                             &res,
                                                             nullptr,
                                                             ".",
                                                             getDocumentManagerView(),
                                                             &_asyncProgress);

        initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant la suppression du resultat du(des) document(s)."));

        _future = QtConcurrent::run(staticRemoveAllItemDrawableOfResultFromView, infoActionID);
        _futureWatcher.setFuture(_future);

        return true;
    }

    return false;
}

bool DM_GuiManager::syncRemoveAllItemDrawableOfResultFromView(CT_AbstractResult& res)
{
    ActionItemDrawable infoActionID = ActionItemDrawable(nullptr,
                                                         &res,
                                                         nullptr,
                                                         ".",
                                                         getDocumentManagerView(),
                                                         &_asyncProgress);

    staticRemoveAllItemDrawableOfResultFromView(infoActionID);
    return true;
}

bool DM_GuiManager::asyncRemoveAllItemDrawableOfModelFromAllViews(CT_OutAbstractItemModel &model, DM_Context *context)
{
    if(model.result() == nullptr)
        return false;

    DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

    if(aop != nullptr)
    {
        if(context != nullptr)
            connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

        ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                             nullptr,
                                                             nullptr,
                                                             ".",
                                                             getDocumentManagerView(),
                                                             &_asyncProgress);
        infoActionID.setItemModel(&model);

        initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant la suppression des items du(des) document(s)."));

        _future = QtConcurrent::run(staticRemoveAllItemDrawablOfModelFromAllViews, infoActionID);
        _futureWatcher.setFuture(_future);

        return true;
    }

    return false;
}

bool DM_GuiManager::asyncRemoveAllItemDrawableOfModelFromView(CT_OutAbstractItemModel &model, DM_DocumentView &view, DM_Context *context)
{
    if(model.result() == nullptr)
        return false;

    DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

    if(aop != nullptr)
    {
        if(context != nullptr)
            connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

        ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                             nullptr,
                                                             nullptr,
                                                             ".",
                                                             getDocumentManagerView(),
                                                             &_asyncProgress);
        infoActionID.setItemModel(&model);
        infoActionID.setDocumentView(&view);

        initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant la suppression des items du document."));

        _future = QtConcurrent::run(staticRemoveAllItemDrawableOfModelFromView, infoActionID);
        _futureWatcher.setFuture(_future);

        return true;
    }

    return false;
}

bool DM_GuiManager::asyncRemoveAllItemDrawableOfListFromView(QList<CT_AbstractItemDrawable *> &itemList, DM_DocumentView *view, DM_Context *context)
{
    if((!getStepManager()->isRunning()
            || !getStepManager()->getOptions().isAutoClearResultFromMemoryEnable()))
    {
        DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

        if(aop != nullptr)
        {
            if(context != nullptr)
                connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

            ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                                 nullptr,
                                                                 &itemList,
                                                                 ".",
                                                                 getDocumentManagerView(),
                                                                 &_asyncProgress);
            infoActionID.setDocumentView(view);

            initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant la suppression des CT_AbstractItemDrawable du document actif."));

            _future = QtConcurrent::run(staticRemoveAllItemDrawableOfListFromView, infoActionID);
            _futureWatcher.setFuture(_future);

            return true;
        }
    }

    return false;
}

bool DM_GuiManager::asyncRemoveStep(CT_VirtualAbstractStep &step, DM_Context *context)
{
    DM_AbstractAsyncOperationOptions options;
    options.setWaitUntilStepManagerIsFinished(true);

    DM_AsyncOperation *aop = requestExclusiveAsyncOperation(&options, false);

    if(aop != nullptr)
    {
        if(context != nullptr)
            connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

        ActionStep infoActionStep = ActionStep(aop,
                                               &step,
                                               getStepManager(),
                                               getDocumentManagerView(),
                                               &_asyncProgress,
                                               &_asyncSecondProgress,
                                               0,
                                               0);

        initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant la suppression de l'etape."));

        recursiveDeleteStepConfigurationDialog(step);

        _future = QtConcurrent::run(staticClearResultMemoryAndRemoveStep, infoActionStep);
        _futureWatcher.setFuture(_future);

        return true;
    }

    return false;
}

int DM_GuiManager::asyncRemoveAllStep(DM_Context *context)
{
    DM_AbstractAsyncOperationOptions options;
    options.setWaitUntilStepManagerIsFinished(true);

    DM_AsyncOperation *aop = requestExclusiveAsyncOperation(&options, false);

    if(aop != nullptr)
    {
        if(context != nullptr)
            connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

        ActionStep infoActionStep = ActionStep(aop,
                                               nullptr,
                                               getStepManager(),
                                               getDocumentManagerView(),
                                               &_asyncProgress,
                                               &_asyncSecondProgress,
                                               0,
                                               0);

        if(!infoActionStep._stepManager->getStepRootList().isEmpty())
        {
            initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant la suppression des etapes."));

            QList<CT_VirtualAbstractStep*> stepRootList = infoActionStep._stepManager->getStepRootList();
            QListIterator<CT_VirtualAbstractStep*> it(stepRootList);

            while(it.hasNext())
            {
                CT_VirtualAbstractStep *step = it.next();

                recursiveDeleteStepConfigurationDialog(*step);
            }

            _future = QtConcurrent::run(staticClearResultMemoryAndRemoveStep, infoActionStep);
            _futureWatcher.setFuture(_future);

            CT_VirtualAbstractStep::resetCurrentID();

            return 1;
        }

        delete aop;

        return -1;
    }

    return 0;
}

bool DM_GuiManager::asyncExport(CT_AbstractExporter *exporter,
                                DM_Context *context)
{
    exporter->clearErrorMessage();

    if(!exporter->configure())
        return false;

    DM_AsyncOperation *aop = requestExclusiveAsyncOperation();

    if(aop != nullptr)
    {
        if(context != nullptr)
            connect(aop, SIGNAL(destroyed()), context, SLOT(setActionFinished()), Qt::DirectConnection);

        ActionItemDrawable infoActionID = ActionItemDrawable(aop,
                                                             nullptr,
                                                             nullptr,
                                                             "",
                                                             nullptr,
                                                             &_asyncProgress);

        infoActionID.setIExporter(exporter);

        initProgressDialog(aop->progressDialog(), tr("Veuillez patienter pendant l'exportation."));

        connect(exporter, SIGNAL(exportInProgress(int)), aop->progressDialog(), SLOT(setValue(int)));

        _future = QtConcurrent::run(staticExport, infoActionID);
        _futureWatcher.setFuture(_future);

        return true;
    }

    return false;
}

bool DM_GuiManager::setColorOnAllItemDrawableOnAllDocumentsThatModelCorresponding(const CT_OutAbstractItemModel *model, const QColor &color)
{
    if(!isRunning())
    {
        int size = getDocumentManagerView()->nbDocumentView();

        for(int i=0; i<size; ++i)
        {
            DM_DocumentView *doc = getDocumentManagerView()->getDocumentView(i);

            if(doc->useItemColor())
            {
                QListIterator<CT_AbstractItemDrawable*> it(doc->getItemDrawable());

                while(it.hasNext())
                {
                    CT_AbstractItemDrawable *item = it.next();

                    if(item->model() == model)
                        doc->setColor(item, color);
                }

                doc->redrawGraphics();
            }
        }

        return true;
    }

    return false;
}

bool DM_GuiManager::setColorListOnAllItemDrawableOnAllDocumentsThatModelCorresponding(const CT_OutAbstractItemModel *model, const QList<QColor> &colorList)
{
    if(!isRunning()
            && !colorList.isEmpty())
    {
        int cSize = colorList.size();
        int size = getDocumentManagerView()->nbDocumentView();

        int j = 0;

        for(int i=0; i<size; ++i)
        {
            DM_DocumentView *doc = getDocumentManagerView()->getDocumentView(i);

            if(doc->useItemColor())
            {
                QListIterator<CT_AbstractItemDrawable*> it(doc->getItemDrawable());

                while(it.hasNext())
                {
                    CT_AbstractItemDrawable *item = it.next();

                    if(item->model() == model)
                    {
                        doc->setColor(item, colorList.at(j));
                        ++j;

                        if(j == cSize)
                            j = 0;
                    }
                }

                doc->redrawGraphics();
            }
        }

        return true;
    }

    return false;
}

bool DM_GuiManager::editItemDrawableModelOfResult(CT_AbstractResult &res)
{
    getItemDrawableModelManager()->addResult(&res);
    return true;
}

bool DM_GuiManager::removeEditItemDrawableModelOfResult(CT_AbstractResult &res)
{
    return getItemDrawableModelManager()->removeResult(&res);
}

bool DM_GuiManager::cleanItemDrawableOfAllDocuments()
{
    if(!isRunning())
    {
        int size = getDocumentManagerView()->nbDocumentView();

        for(int i=0; i<size; ++i)
        {
            DM_DocumentView *doc = getDocumentManagerView()->getDocumentView(i);

            doc->removeAllItemDrawable();

            doc->redrawGraphics();
        }

        getItemDrawableModelManager()->reconstruct();

        return true;
    }

    return false;
}

bool DM_GuiManager::isRunning()
{
    return _futureWatcher.isRunning() || isAsyncOperationInProgress();
}

void DM_GuiManager::redrawAllDocuments()
{
    getDocumentManagerView()->redrawAllDocument();
}

CDM_PluginManager* DM_GuiManager::getPluginManager() const
{
    return getMainWindow()->getPluginManager();
}

///////////////// PROTECTED /////////////////

void DM_GuiManager::init()
{
    m_currentAsyncOperation = nullptr;

    connect(getStepManager(), SIGNAL(resultToBeClearedFromMemory(const CT_AbstractResult*)), this, SLOT(resultToBeClearedFromMemory(const CT_AbstractResult*)), Qt::DirectConnection);
    connect(getStepManager(), SIGNAL(resultToBeRemoved(const CT_AbstractResult*)), this, SLOT(resultToBeRemoved(const CT_AbstractResult*)), Qt::DirectConnection);

    _progressDialog = getMainWindow()->createWaitProgressDialog();

    connect(&_futureWatcher, SIGNAL(finished()), &_asyncProgress, SLOT(finish()), Qt::QueuedConnection);
}

///////////////// PRIVATE /////////////////

void DM_GuiManager::initProgressDialog(IMainProgressDialog *dialog, QString text, QString secondText)
{
    if(dialog != nullptr)
    {
        connect(&_asyncProgress, SIGNAL(inProgress(int)), dialog, SLOT(setValue(int)), Qt::QueuedConnection);
        connect(&_asyncProgress, SIGNAL(textChanged(QString)), dialog, SLOT(setLabelText(QString)), Qt::QueuedConnection);

        connect(&_asyncSecondProgress, SIGNAL(textChanged(QString)), dialog, SLOT(setSecondLabelText(QString)), Qt::QueuedConnection);
        connect(&_asyncSecondProgress, SIGNAL(inProgress(int)), dialog, SLOT(setSecondValue(int)), Qt::QueuedConnection);

        dialog->setWindowModality(Qt::WindowModal);
        dialog->setCanClose(false);
        dialog->setLabelText(text);
        dialog->setSecondLabelText(secondText);
        dialog->setValue(0);
        dialog->show();
    }
}

void DM_GuiManager::addNewContext(DM_Context *context)
{
    if(context != nullptr)
    {
        _contextList.append(context);

        if(_contextList.size() == 11)
        {
            delete _contextList.takeFirst();
        }
    }
}

void DM_GuiManager::recursiveDeleteStepConfigurationDialog(CT_VirtualAbstractStep& step)
{
    step.aboutToBeDeleted();

    step.recursiveVisitChildrens([](const CT_VirtualAbstractStep*, const CT_VirtualAbstractStep* child) -> bool {
        const_cast<CT_VirtualAbstractStep*>(child)->aboutToBeDeleted();
        return true;
    });
}

void DM_GuiManager::staticRemoveResultFromOtherView(ActionItemDrawable info)
{
    if(info._res != nullptr)
    {
        if(info._res->isVisible())
        {
            info._progress->setText(QObject::tr("Suppression du résultat %1 des autres vues.").arg(info._res->displayableName()));
            info._view->removeAllItemDrawableOfResultFromDocuments(*info._res, *info._progress);
            info._progress->setText("");
        }
    }

    delete info._aop;
}

void DM_GuiManager::staticAddAllItemDrawableOfResultOnView(ActionItemDrawable info)
{
    info._view->addAllItemDrawableOfResultToActiveDocument(*(info._res), *(info._progress));

    delete info._aop;
}

void DM_GuiManager::staticAddAllItemDrawableOfModelOnView(ActionItemDrawable info)
{
    info._view->addAllItemDrawableOfModelToDocument(*(info._res), *(info._itemModel), info.m_docView, *(info._progress));

    delete info._aop;
}

void DM_GuiManager::staticAddAllItemDrawableOfListOnView(ActionItemDrawable info)
{
    if(info.m_docView == nullptr)
        info._view->addAllItemDrawableOfListToActiveDocument(info._itemList, *(info._progress));
    else
        info._view->addAllItemDrawableOfListToDocument(info._itemList, info.m_docView, *(info._progress));

    delete info._aop;
}

void DM_GuiManager::staticRemoveAllItemDrawableOfResultFromView(ActionItemDrawable info)
{
    info._view->removeAllItemDrawableOfResultFromDocuments(*(info._res), *(info._progress));

    delete info._aop;
}

void DM_GuiManager::staticRemoveAllItemDrawablOfModelFromAllViews(ActionItemDrawable info)
{
    info._view->removeAllItemDrawableOfModelFromDocuments(*(info._itemModel), *(info._progress));

    delete info._aop;
}

void DM_GuiManager::staticRemoveAllItemDrawableOfModelFromView(ActionItemDrawable info)
{
    info._view->removeAllItemDrawableOfModelFromDocument(*(info._itemModel), info.m_docView, *(info._progress));

    delete info._aop;
}

void DM_GuiManager::staticRemoveAllItemDrawableOfListFromView(ActionItemDrawable info)
{
    if(info.m_docView == nullptr)
        info._view->removeAllItemDrawableOfListFromDocuments(info._itemList, *(info._progress));
    else
        info._view->removeAllItemDrawableOfListFromDocument(info._itemList, info.m_docView, *(info._progress));

    delete info._aop;
}

void DM_GuiManager::staticClearResultMemoryAndRemoveStep(ActionStep info)
{
    if(info._step == nullptr)
    {
        QList<CT_VirtualAbstractStep *> list = info._stepManager->getStepRootList();

        QListIterator<CT_VirtualAbstractStep *> it(list);

        while(it.hasNext())
        {
            info._totalProgressSize += staticRecursiveCountProgress(it.next());
        }

        int nProgress = 0;

        it.toFront();

        while(it.hasNext())
        {
            ActionStep infoRecur = info;
            infoRecur._step = it.next();
            infoRecur._nProgress = nProgress;

            nProgress = staticRecursiveClearResultMemoryAndRemoveStep(infoRecur);
        }
    }
    else
    {
        info._totalProgressSize = staticRecursiveCountProgress(info._step);
        info._nProgress = 0;

        staticRecursiveClearResultMemoryAndRemoveStep(info);
    }

    delete info._aop;
}

int DM_GuiManager::staticRecursiveCountProgress(CT_VirtualAbstractStep *step)
{
    int count = step->nOutResult();

    step->recursiveVisitChildrens([&count](const CT_VirtualAbstractStep*, const CT_VirtualAbstractStep* child) -> bool {
        count += child->nOutResult();
        return true;
    });

    return count;
}

int DM_GuiManager::staticRecursiveClearResultMemoryAndRemoveStep(ActionStep info)
{
    info._step->visitChildrens([&info](const CT_VirtualAbstractStep*, const CT_VirtualAbstractStep* child) -> bool {

        ActionStep infoRecur = info;
        infoRecur._step = const_cast<CT_VirtualAbstractStep*>(child);
        info._nProgress = staticRecursiveClearResultMemoryAndRemoveStep(infoRecur);

        return true;
    });


    info._step->visitOutResults([&info](const CT_AbstractResult* result) -> bool {

        staticRemoveResultFromOtherView(ActionItemDrawable(nullptr,
                                                           const_cast<CT_AbstractResult*>(result),
                                                           nullptr,
                                                           "",
                                                           info._docManagerView,
                                                           info._secondProgress));

        info._nProgress++;
        info._progress->setProgress(((float)(info._nProgress*100))/((float)info._totalProgressSize));

        return true;
    });

    info._step->clearOutResult();
    info._stepManager->removeStep(info._step);

    return info._nProgress;
}

void DM_GuiManager::staticExport(ActionItemDrawable info)
{
    info._exporter->exportToFile();

    delete info._aop;

    info._progress->finish();
    delete info._exporter;
}

///////////////// PRIVATE SLOTS /////////////////

void DM_GuiManager::resultToBeClearedFromMemory(const CT_AbstractResult *res)
{
    staticRemoveResultFromOtherView(ActionItemDrawable(nullptr,
                                                       (CT_AbstractResult*)res,
                                                       nullptr,
                                                       "",
                                                       getDocumentManagerView(),
                                                       &_asyncSecondProgress));
}

void DM_GuiManager::resultToBeRemoved(const CT_AbstractResult *res)
{
    staticRemoveResultFromOtherView(ActionItemDrawable(nullptr,
                                                       (CT_AbstractResult*)res,
                                                       nullptr,
                                                       "",
                                                       getDocumentManagerView(),
                                                       &_asyncSecondProgress));
}

void DM_GuiManager::slotCurrentAsyncOperationDestroyed()
{
    QMutexLocker locker(&m_asyncOperationTokenMutex);

    if(m_currentAsyncOperation->progressDialog() != nullptr)
        m_queueProgressDialogToDestroy.enqueue(m_currentAsyncOperation->progressDialog());

    m_currentAsyncOperation = nullptr;

    if(!m_tokens.isEmpty())
        delete m_tokens.takeFirst();

    locker.unlock();

    emit currentAsyncOperationReleased();
}

void DM_GuiManager::slotCurrentAsyncOperationReleased()
{
    QMutexLocker locker(&m_asyncOperationTokenMutex);

    if(!m_queueProgressDialogToDestroy.isEmpty())
    {
        IMainProgressDialog *pDialog = m_queueProgressDialogToDestroy.dequeue();

        pDialog->setCanClose(true);
        pDialog->close();
        delete pDialog;
    }
}
