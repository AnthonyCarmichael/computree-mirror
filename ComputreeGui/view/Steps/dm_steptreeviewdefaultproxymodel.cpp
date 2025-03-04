#include "dm_steptreeviewdefaultproxymodel.h"

#include <QGuiApplication>

DM_StepTreeViewDefaultProxyModel::DM_StepTreeViewDefaultProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setShowStepNotCompatible(true);
    m_parentStep = nullptr;
    setPluginsFilterEnabled(true);

    m_manualStepFont = QGuiApplication::font();
    m_manualStepFont.setItalic(true);

    setValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::IT_RootLevel, Qt::BackgroundRole, QColor(64, 64, 64));
    setValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::IT_Step, Qt::BackgroundRole, QColor(175, 171, 171));
    setValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::IT_SubLevel, Qt::BackgroundRole, QColor(91, 155, 213));
    setValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::IT_StepNF, Qt::ForegroundRole, QColor(255, 255, 0));

    setValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::IT_All, Qt::ForegroundRole, QColor(255, 255, 255));

    //setValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::IT_All, Qt::TextAlignmentRole, Qt::AlignCenter);

    setFilterConfiguration(FC_StepFullDescription | FC_StepShortDescription | FC_StepDisplayableName);

    setStepsNameFunction(nullptr, nullptr);
}

DM_StepTreeViewDefaultProxyModel::~DM_StepTreeViewDefaultProxyModel()
{
    qDeleteAll(m_values.begin(), m_values.end());
}

void DM_StepTreeViewDefaultProxyModel::setTypeVisible(DM_StepsFromPluginsModelConstructor::ItemType type, bool enable)
{
    if(enable) {
        m_typesNotVisible.removeAll(type);
        return;
    }

    m_typesNotVisible.append(type);

    invalidate();
}

bool DM_StepTreeViewDefaultProxyModel::isTypeVisible(DM_StepsFromPluginsModelConstructor::ItemType type) const
{
    int i = m_typesNotVisible.indexOf(type);

    if(i != -1)
        return false;

    QListIterator<DM_StepsFromPluginsModelConstructor::ItemType> it(m_typesNotVisible);

    while(it.hasNext()) {
        if(it.next() & type)
            return false;
    }

    return true;
}

void DM_StepTreeViewDefaultProxyModel::setValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::ItemType type,
                                                              Qt::ItemDataRole role,
                                                              QVariant val)
{
    QHash<Qt::ItemDataRole, QVariant> *hash = m_values.value(type, nullptr);

    if(hash == nullptr) {
        hash = new QHash<Qt::ItemDataRole, QVariant>();
        m_values.insert(type, hash);
    }

    hash->insert(role, val);
}

QVariant DM_StepTreeViewDefaultProxyModel::getValueForTypeAndRole(DM_StepsFromPluginsModelConstructor::ItemType type, Qt::ItemDataRole role) const
{
    QVariant v;

    QHash<Qt::ItemDataRole, QVariant> *hash = m_values.value(type, nullptr);

    if(hash != nullptr) {
        v = hash->value(role, QVariant());

        if(v.isValid())
            return v;
    }

    QMapIterator<DM_StepsFromPluginsModelConstructor::ItemType, QHash<Qt::ItemDataRole, QVariant> *> it(m_values);

    while(it.hasNext()) {
        it.next();

        if((it.key() != type) && (it.key() & type)) {
            v = it.value()->value(role, QVariant());

            if(v.isValid())
                return v;
        }
    }

    return v;
}

void DM_StepTreeViewDefaultProxyModel::setStepsNameFunction(functionGetStepName f, void *context)
{
    m_stepsNameF = f;
    m_stepsNameContext = context;
}

DM_StepTreeViewDefaultProxyModel::FilterConfigs DM_StepTreeViewDefaultProxyModel::filterConfiguration() const
{
    return m_filterConfig;
}

void DM_StepTreeViewDefaultProxyModel::setUseStepsOfPlugins(const QList<CT_AbstractStepPlugin *> &plugins)
{
    m_plugins = plugins;
    setPluginsFilterEnabled(true);
}

void DM_StepTreeViewDefaultProxyModel::setPluginsFilterEnabled(bool enable)
{
    m_pluginsFilterEnable = enable;

    invalidate();
}

void DM_StepTreeViewDefaultProxyModel::setShowStepNotCompatible(bool enable)
{
    m_showNotCompatible = enable;

    invalidate();
}

void DM_StepTreeViewDefaultProxyModel::setFilterConfiguration(FilterConfigs configs)
{
    m_filterConfig = configs;

    invalidate();
}

void DM_StepTreeViewDefaultProxyModel::setParentStep(CT_VirtualAbstractStep *parent)
{
    if(m_parentStep != nullptr)
        disconnect(m_parentStep, nullptr, this, nullptr);

    m_parentStep = parent;
    m_backupStepCompatibleWithParent.clear();

    if(m_parentStep != nullptr)
        connect(m_parentStep, SIGNAL(destroyed()), this, SLOT(parentStepDestroyed()), Qt::DirectConnection);

    invalidate();
}

CT_VirtualAbstractStep* DM_StepTreeViewDefaultProxyModel::parentStep() const
{
    return m_parentStep;
}

QVariant DM_StepTreeViewDefaultProxyModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::BackgroundRole) {
        if(isIndexOfType(index, DM_StepsFromPluginsModelConstructor::IT_Step, DM_StepsFromPluginsModelConstructor::DR_SecondaryType)) {

            if(!isStepCompatibleWithParent(index))
                return QColor(240, 70, 79); // red color for step not compatible
        }
    }

    if(role == Qt::FontRole) {
        if(isIndexOfType(index, DM_StepsFromPluginsModelConstructor::IT_Step)) {

            CT_VirtualAbstractStep *step = getStepFromIndex(index);

            if((step != nullptr) && step->isManual())
                return m_manualStepFont; // special font for manual step
        }
    }

    if(role < Qt::UserRole + 1) {
        if((m_stepsNameF != nullptr) && (role == Qt::DisplayRole) && isIndexOfType(index, DM_StepsFromPluginsModelConstructor::IT_Step)) {

            QString str;

            if((*m_stepsNameF)(str, index, m_stepsNameContext))
                return str;
        }

        QVariant v = getValueForTypeAndRole((DM_StepsFromPluginsModelConstructor::ItemType)index.data(DM_StepsFromPluginsModelConstructor::DR_SecondaryType).toInt(), (Qt::ItemDataRole)role);

        if(v.isValid())
            return v;
    }

    return QSortFilterProxyModel::data(index, role);
}

bool DM_StepTreeViewDefaultProxyModel::pluginsFilterEnabled() const
{
    return m_pluginsFilterEnable;
}

QList<CT_AbstractStepPlugin *> DM_StepTreeViewDefaultProxyModel::pluginsForFiltering() const
{
    return m_plugins;
}

bool DM_StepTreeViewDefaultProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if(sourceModel() != nullptr) {

        return recursiveAcceptRow(sourceModel()->index(source_row, 0, source_parent));
    }

    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

bool DM_StepTreeViewDefaultProxyModel::recursiveAcceptRow(const QModelIndex &index) const
{
    if(index.isValid())
    {
        int s = sourceModel()->rowCount(index);

        if(s > 0) {
            int i = 0;
            bool notEmpty = false;

            while((i < s) && !notEmpty) {
                if(recursiveAcceptRow(index.model()->index(i, 0, index)))
                    notEmpty = true;

                ++i;
            }

            if(!notEmpty)
                return false;
        }

        if(!isTypeVisible(getTypeFromIndex(index, DM_StepsFromPluginsModelConstructor::DR_SecondaryType)))
            return false;

        if(isIndexOfType(index, DM_StepsFromPluginsModelConstructor::IT_Step, DM_StepsFromPluginsModelConstructor::DR_SecondaryType))
        {
            if(!acceptStep(index, pluginsFilterEnabled()))
                return false;
        }

        return true;
    }

    return false;
}

bool DM_StepTreeViewDefaultProxyModel::isIndexOfType(const QModelIndex &index, DM_StepsFromPluginsModelConstructor::ItemType type, DM_StepsFromPluginsModelConstructor::DataRole dataRole) const
{
    return (getTypeFromIndex(index, dataRole) & type);
}

CT_VirtualAbstractStep *DM_StepTreeViewDefaultProxyModel::getStepFromIndex(const QModelIndex &index) const
{
    return (CT_VirtualAbstractStep*)index.model()->sibling(index.row(), 0, index).data(DM_StepsFromPluginsModelConstructor::DR_Pointer).value<void*>();
}

DM_StepsFromPluginsModelConstructor::ItemType DM_StepTreeViewDefaultProxyModel::getTypeFromIndex(const QModelIndex &index, DM_StepsFromPluginsModelConstructor::DataRole dataRole) const
{
    return (DM_StepsFromPluginsModelConstructor::ItemType)index.data(dataRole).toInt();
}

bool DM_StepTreeViewDefaultProxyModel::acceptStep(const QModelIndex &index, bool usePluginFiltered) const
{
    if(usePluginFiltered && !existStepInPluginCollection(index))
        return false;

    if(filterRegExp().isValid()
            && !filterRegExp().isEmpty()) {

        bool accepted = false;
        CT_VirtualAbstractStep *step = getStepFromIndex(index);

        if(step != nullptr) {
            if(m_filterConfig.testFlag(FC_StepKey)
                    && filterRegExp().exactMatch(step->pluginStaticCastT<>()->getKeyForStep(*step)))
                accepted = true;

            if(!accepted
                    && m_filterConfig.testFlag(FC_StepDisplayableName)
                    && filterRegExp().exactMatch(step->displayableCustomName()))
                accepted = true;

            if(!accepted
                    && m_filterConfig.testFlag(FC_StepShortDescription)
                    && filterRegExp().exactMatch(step->description()))
                accepted = true;

            if(!accepted
                    && m_filterConfig.testFlag(FC_StepFullDescription)
                    && filterRegExp().exactMatch(step->detailledDescription()))
                accepted = true;
        }

        if(!accepted)
            return false;
    }

    return m_showNotCompatible || isStepCompatibleWithParent(index);
}

bool DM_StepTreeViewDefaultProxyModel::existStepInPluginCollection(const QModelIndex &index) const
{
    CT_VirtualAbstractStep *step = getStepFromIndex(index);

    if(step == nullptr)
        return false;

    return m_plugins.contains(step->pluginStaticCastT<>());
}

bool DM_StepTreeViewDefaultProxyModel::isStepCompatibleWithParent(const QModelIndex &index) const
{
    CT_VirtualAbstractStep *step = getStepFromIndex(index);

    if(step == nullptr)
        return false;

    int val = m_backupStepCompatibleWithParent.value(step, 2);

    if(val == 2) {
        bool compatible = step->acceptAddAfterThisStep(m_parentStep);

        const_cast<DM_StepTreeViewDefaultProxyModel*>(this)->m_backupStepCompatibleWithParent.insert(step, (compatible ? 1 : 0));

        return compatible;
    }

    return (val == 1);
}

void DM_StepTreeViewDefaultProxyModel::parentStepDestroyed()
{
    m_parentStep = nullptr;
}
