#pragma once
class KDSize {
public:
    constexpr KDSize(int width, int height) :
        m_width(width), m_height(height) {}
    constexpr int width() const { return m_width; }
    constexpr int height() const { return m_height; }
    bool operator==(const KDSize& other) const {
        return m_width == other.width() && m_height == other.height();
    }
private:
    int m_width;
    int m_height;
};

constexpr KDSize KDSizeZero = KDSize(0, 0);