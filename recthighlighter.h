#ifndef RECTHIGHLIGHTER_H
#define RECTHIGHLIGHTER_H

#include "ocdglobals.h"
#include "highlighter.h"
#include "roundedrect.h"

/**
 * @brief The RectHighlighter class handles selecting the highlight point for rectangles.
 */
class RectHighlighter : public Highlighter
{
public:
    RectHighlighter(const RoundedRect* rect);
    virtual ~RectHighlighter() override;

    bool isInRange(QPointF cursor) const override;
    QPointF selectPoint(QPointF cursor) const override;

private:
    const RoundedRect* rect;

    static bool isInside(qreal value, qreal min, qreal size);
    static bool isOutside(qreal value, qreal min, qreal size);
};
Q_DECLARE_METATYPE(RectHighlighter*)

#endif // RECTHIGHLIGHTER_H
