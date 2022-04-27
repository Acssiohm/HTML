#pragma once

class KDPoint {
public:
    constexpr KDPoint(int x, int y) :
        m_x(x), m_y(y) {}
    int x() const { return m_x; }
    int y() const { return m_y; }
    KDPoint translatedBy(KDPoint other) const;
    KDPoint opposite() const;
    bool operator ==(const KDPoint& other) const {
        return (m_x == other.m_x && m_y == other.m_y);
    }
    bool operator !=(const KDPoint& other) const {
        return !(operator ==(other));
    }
    int squareDistanceTo(KDPoint other) const;

    int m_x;
    int m_y;
};

constexpr KDPoint KDPointZero = KDPoint(0, 0);
