#include "CTVSet.h"

class CTVSet {
public:
    void TurnOn();
    void TurnOff(); 
    void SelectChannel(const int channelNumber);
    

private:
    bool m_turn = false;
    int m_previosChannel = 1;
    int m_currentChannel = 1;
    const int m_maxChannel = 99;
    const int m_minChannel = 1;

};


void CTVSet::TurnOn() {
    m_turn = true;
    m_currentChannel = m_previosChannel;
}

void CTVSet::TurnOff() {
    m_turn = false;
    m_previosChannel = m_currentChannel;
    m_currentChannel = 0;
}


void CTVSet::SelectChannel(const int channelNumber) {
    if (m_minChannel <= channelNumber <= m_maxChannel && m_turn == true) {
        m_previosChannel = m_currentChannel;
        m_currentChannel = channelNumber;
    }
}