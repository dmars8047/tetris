#ifndef SCREEN_CONFIG_HPP
#define SCREEN_CONFIG_HPP

class ScreenConfig
{
private:
    int m_BlockSize;
    int m_ViewPortWidth;
    int m_ViewPortHeight;
public:
    ScreenConfig();
    int GetBlockSize() const;
    int GetViewPortHeight() const;
    int GetViewPortWidth() const; 
};

#endif