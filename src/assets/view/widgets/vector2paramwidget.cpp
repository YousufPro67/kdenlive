/*
    SPDX-FileCopyrightText: 2024 Custom Implementation
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "vector2paramwidget.hpp"
#include "assets/model/assetparametermodel.hpp"

#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>

Vector2ParamWidget::Vector2ParamWidget(std::shared_ptr<AssetParameterModel> model, QModelIndex index, QWidget *parent)
    : AbstractParamWidget(std::move(model), index, parent)
    , m_labelComment(nullptr)
{
    auto *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    
    // Get vector info from model
    auto vectorInfo = m_model->data(m_index, AssetParameterModel::Vector2Info).value<AssetVectorInfo>();
    
    // Create labels and spinboxes
    auto *labelX = new QLabel(QString::fromUtf8(vectorInfo.destNameX.isEmpty() ? "X" : vectorInfo.destNameX.toLatin1()), this);
    m_spinX = new QDoubleSpinBox(this);
    m_spinX->setMinimum(vectorInfo.minimum.x());
    m_spinX->setMaximum(vectorInfo.maximum.x());
    m_spinX->setValue(vectorInfo.defaultValue.x());
    m_spinX->setDecimals(3);
    m_spinX->setSingleStep(0.1);
    
    auto *labelY = new QLabel(QString::fromUtf8(vectorInfo.destNameY.isEmpty() ? "Y" : vectorInfo.destNameY.toLatin1()), this);
    m_spinY = new QDoubleSpinBox(this);
    m_spinY->setMinimum(vectorInfo.minimum.y());
    m_spinY->setMaximum(vectorInfo.maximum.y());
    m_spinY->setValue(vectorInfo.defaultValue.y());
    m_spinY->setDecimals(3);
    m_spinY->setSingleStep(0.1);
    
    lay->addWidget(labelX);
    lay->addWidget(m_spinX, 1);
    lay->addWidget(labelY);
    lay->addWidget(m_spinY, 1);
    lay->addStretch();
    
    connect(m_spinX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Vector2ParamWidget::slotValueChanged);
    connect(m_spinY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Vector2ParamWidget::slotValueChanged);
}

QVector3D Vector2ParamWidget::parseValue(const QString &value)
{
    const QStringList parts = value.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (parts.count() >= 2) {
        return QVector3D(parts.at(0).toDouble(), parts.at(1).toDouble(), 0.0);
    }
    return QVector3D(0, 0, 0);
}

QString Vector2ParamWidget::valuesToString(double x, double y)
{
    return QStringLiteral("%1 %2").arg(x).arg(y);
}

void Vector2ParamWidget::slotValueChanged()
{
    QString value = valuesToString(m_spinX->value(), m_spinY->value());
    Q_EMIT valueChanged(m_index, value, true);
}

void Vector2ParamWidget::slotRefresh()
{
    const QString value = m_model->data(m_index, AssetParameterModel::ValueRole).toString();
    if (!value.isEmpty()) {
        QVector3D vec = parseValue(value);
        m_spinX->blockSignals(true);
        m_spinY->blockSignals(true);
        m_spinX->setValue(vec.x());
        m_spinY->setValue(vec.y());
        m_spinX->blockSignals(false);
        m_spinY->blockSignals(false);
    }
}

void Vector2ParamWidget::slotShowComment(bool show)
{
    if (m_labelComment) {
        m_labelComment->setVisible(show);
    }
}
