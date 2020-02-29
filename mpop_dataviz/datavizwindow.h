#pragma once

#include "openglwindow.h"
#include "sceneobject.h"
#include <QtGui/QOpenGLShaderProgram>
#include <QElapsedTimer>
#include <QVector>


class DatavizWindow : public OpenGLWindow {
public:
    DatavizWindow();
    ~DatavizWindow() override;
    void initialize() override;
    void render() override;

private:
    QElapsedTimer _elapsedTimer;
    QVector<SceneObject*> _sceneObjects;
};
