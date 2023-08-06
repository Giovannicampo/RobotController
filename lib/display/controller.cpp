#include "controller.h"

Controller::Controller(Mrf24j* mrf, Display* display)

{
    this->mrf = mrf;
    this->display = display;
    this->display->setController(this);
}

void Controller::handleRx()
{
    // Serial.printf("PANID: %04x | DEST: %04x | SOURCE: %04x | LQI: %d | RSSI: %d \n", mrf->get_rxinfo()->panid,  mrf->get_rxinfo()->dest_addr,  mrf->get_rxinfo()->src_addr, mrf->get_rxinfo()->lqi, mrf->get_rxinfo()->rssi);
    // Serial.print(mrf->get_rxinfo()->panid);
    
    uint8_t * _data = (uint8_t*)mrf->get_rxinfo()->rx_data;
    uint16_t addr_robot = mrf->get_rxinfo()->src_addr;

    onReceive(_data, addr_robot);
}

void Controller::handleTx()
{
    if (mrf->get_txinfo()->tx_ok) {
        Serial.println("TX went ok, got ack");
    } else {
        Serial.print("TX failed after ");Serial.print(mrf->get_txinfo()->retries);Serial.println(" retries\n");
    }
}

uint8_t* Controller::onTrasmission()
{
    if(this->display->onRadioTransmit() == nullptr){
        return nullptr;
    }
    Serial.println("sto trasmettendo");
    uint8_t* data = this->display->onRadioTransmit();
    return data;
}

void Controller::onReceive(uint8_t* _data, uint16_t addr_robot)
{
    display->onRadioReceive(_data, addr_robot);
}