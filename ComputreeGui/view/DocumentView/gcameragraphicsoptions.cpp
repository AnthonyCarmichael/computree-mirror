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


#include "gcameragraphicsoptions.h"
#include "ui_gcameragraphicsoptions.h"


#include <QToolButton>
#include <QMenu>
#include <QWidgetAction>

GCameraGraphicsOptions::GCameraGraphicsOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GCameraGraphicsOptions)
{
    ui->setupUi(this);
    ui->toolButtonCameraCoordinate->setPopupMode(QToolButton::InstantPopup);

    _camera = nullptr;
    _camCoordinateWidget = new GCameraCoordinatesOptions(this);

    QMenu *menu = new QMenu(ui->toolButtonCameraCoordinate);
    QWidgetAction *wAction = new QWidgetAction(menu);
    wAction->setDefaultWidget(_camCoordinateWidget);
    ui->toolButtonCameraCoordinate->setMenu(menu);
    menu->addAction(wAction);

    ui->comboBoxPointOfView->addItem(QIcon(":/Icones/Icones/top.png"),"");
    ui->comboBoxPointOfView->addItem(QIcon(":/Icones/Icones/bottom.png"),"");
    ui->comboBoxPointOfView->addItem(QIcon(":/Icones/Icones/left.png"),"");
    ui->comboBoxPointOfView->addItem(QIcon(":/Icones/Icones/right.png"),"");
    ui->comboBoxPointOfView->addItem(QIcon(":/Icones/Icones/front.png"),"");
    ui->comboBoxPointOfView->addItem(QIcon(":/Icones/Icones/back.png"),"");
    ui->comboBoxPointOfView->setCurrentIndex(4); // front

    ui->comboBoxPivotPoint->addItem(QIcon(":/Icones/Icones/center_on_0.png"),"");
    ui->comboBoxPivotPoint->addItem(QIcon(":/Icones/Icones/center_on_scene.png"),"");
    ui->comboBoxPivotPoint->addItem(QIcon(":/Icones/Icones/center_on_selected.png"),"");
    ui->comboBoxPivotPoint->setCurrentIndex(0);

    ui->comboBoxPivotPoint->setToolTip("Définir le point de pivot....");
    ui->comboBoxPivotPoint->setItemData(0, tr("Définir le point de pivot à l'origine (0,0,0)"), Qt::ToolTipRole);
    ui->comboBoxPivotPoint->setItemData(1, tr("Définir le point de pivot au barycentre des éléments visibles"), Qt::ToolTipRole);
    ui->comboBoxPivotPoint->setItemData(2, tr("Définir le point de pivot au barycentre des éléments sélectionnés"), Qt::ToolTipRole);

    setPushButtonSyncToolTip();
}

GCameraGraphicsOptions::~GCameraGraphicsOptions()
{
    delete ui;
}

void GCameraGraphicsOptions::setCamera(const DM_GraphicsViewCamera *camera)
{
    _camera = (DM_GraphicsViewCamera*)camera;
    _camCoordinateWidget->setCameraController(_camera);
}

void GCameraGraphicsOptions::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void GCameraGraphicsOptions::setPushButtonSyncToolTip()
{
    ui->pushButtonSync->setToolTip(ui->pushButtonSync->isChecked() ? tr("Desynchroniser ce document") : tr("Synchroniser ce document"));
}

void GCameraGraphicsOptions::on_pushButtonSync_toggled(bool toggle)
{
    Q_UNUSED(toggle)

    setPushButtonSyncToolTip();

    emit syncGraphics(ui->pushButtonSync->isChecked());
}

void GCameraGraphicsOptions::on_pushButtonFitMagic_clicked()
{
    if(_camera != nullptr)
    {
        _camera->fixCameraCenterToItemsBarycenter();
        _camera->fitCameraToVisibleItems();
    }
}

void GCameraGraphicsOptions::on_comboBoxPointOfView_activated(int index)
{
    if(_camera != nullptr)
    {
        if      (index == 0) {_camera->alignCameraToZAxis();}
        else if (index == 1) {_camera->alignCameraToInvZAxis();}
        else if (index == 2) {_camera->alignCameraToYAxis();}
        else if (index == 3) {_camera->alignCameraToInvYAxis();}
        else if (index == 4) {_camera->alignCameraToXAxis();}
        else if (index == 5) {_camera->alignCameraToInvXAxis();}
    }
}

void GCameraGraphicsOptions::on_comboBoxPivotPoint_activated(int index)
{
    if(_camera != nullptr)
    {
        if(index == 2) { _camera->fixCameraCenterToSelectedItemsBarycenter(); }
        else if(index == 1) { _camera->fixCameraCenterToItemsBarycenter(); }
        else if(index == 0) { _camera->initCameraCenter(); }
    }
}
