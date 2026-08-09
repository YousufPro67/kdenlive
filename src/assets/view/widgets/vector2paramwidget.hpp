/*
    SPDX-FileCopyrightText: 2024 Custom Implementation
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include "abstractparamwidget.hpp"
#include <QVector3D>

class QDoubleSpinBox;
class QLabel;

class Vector2ParamWidget : public AbstractParamWidget
{
    Q_OBJECT
public:
    explicit Vector2ParamWidget(std::shared_ptr<AssetParameterModel> model, QModelIndex index, QWidget *parent);
    ~Vector2ParamWidget() override = default;

public Q_SLOTS:
    void slotShowComment(bool show) override;
    void slotRefresh() override;

private Q_SLOTS:
    void slotValueChanged();

private:
    QDoubleSpinBox *m_spinX;
    QDoubleSpinBox *m_spinY;
    QLabel *m_labelComment;
    
    QVector3D parseValue(const QString &value);
    QString valuesToString(double x, double y);
};
