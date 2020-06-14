#pragma once

#include <QPointF>
#include <QElapsedTimer>
#include <algorithm>
#include <QSharedPointer>

#include "barchartlayout.h"
#include "screensaverlayout.h"

class ViewModeManager
{
public:
    // Types:
    enum ViewMode {
        ScreenSaverMode, // Default Mode
        UserAnswersMode, // See My answer
        FairnessAnswersMode,
        AnswerByAgeMode,
        AnswerByGenderMode,
        AnswerByCultureMode
    };

    typedef  QSharedPointer<QVector<PrisonerLine::ptr>> viewBars;

    typedef struct {
        QString text;
        int my_answer;
        int their_answer;
    } AnswerData;

    typedef QSharedPointer<AnswerData> AnswerDataPtr;

    // Methods:
    ViewModeManager();
    ~ViewModeManager() {}

    void showViewManagerBars(ViewMode mode);

    void updateViewCoordinate(qreal left, qreal right, qreal bottom, qreal top);
    void updateViewSize(int width, int height);

    void setViewActiveMode(ViewMode mode);
    ViewMode getViewActiveMode() const { return _viewActiveMode; }

    void setBarChartRows(const QList<int> &list, ViewMode viewIndex);
    void moveBarsToLayouts(ViewModeManager::viewBars bars, ViewMode viewIndex);

    void setViewBarsQuantity(int number, ViewMode viewIndex);

    ViewModeManager::viewBars getBarsFromScreenSaver(int number);

    void setUserAnswerBars(const QList<int> &bars);
    void setFairnessAnswerBars();

    QPointF coordinateFromPixel(qreal x, qreal y);
    QPointF sizeFromPixel(qreal width, qreal height);

    void setPointToPickFrom(const QPointF &point);

    qreal mapValue(qreal value, qreal istart, qreal istop, qreal ostart, qreal ostop);

    qint64 currentTime() { return _timer.elapsed(); }

    // View mode manager singleton
    static ViewModeManager *viewManager() {
        if (viewModeManager == nullptr)
            viewModeManager = new ViewModeManager;
        return viewModeManager;
    }

    void showAnswersData(const QList<AnswerDataPtr>& answers);

private:
    ViewMode _viewActiveMode;

    qreal _left, _right, _bottom, _top;

    int _width, _height;

    QPointF _pointToPickFrom;

    QVector<ViewModeManager::viewBars> _viewBars;

    ScreensaverLayout _screensaver;
    BarChartLayout _userAnswers;

    QVector<BarChartLayout> _fairnessAverageAnswer;
    QVector<BarChartLayout> _fairnessUserAnswer;

    QElapsedTimer _timer;

    static ViewModeManager *viewModeManager;
};