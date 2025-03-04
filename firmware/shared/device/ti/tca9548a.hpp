#pragma once

#include <sys/_stdint.h>
#include "shared/device/i2c_mux.hpp"
#include "shared/periph/i2c.hpp"
#include <iostream>
#include <string>

namespace shared::device::ti {

enum class TCA9548AChannel : uint8_t {
    INVALID = 0xFF,
    CHANNEL_A = 0,
    CHANNEL_B = 1,
    CHANNEL_C = 2,
    CHANNEL_D = 3,
    CHANNEL_E = 4,
    CHANNEL_F = 5,
    CHANNEL_G = 6,
    CHANNEL_H = 7,
};

class TCA9548A : public I2CMultiplexer<TCA9548AChannel> {
private:
    enum class ChannelStatus : uint8_t {
        UNSELECTED = 0,
        SELECTED = 1,
    };

public:
    constexpr TCA9548A(shared::periph::I2CBus& i2c_bus, uint8_t mux_address,
             bool force_select = false)
        : I2CMultiplexer<TCA9548AChannel>(i2c_bus, mux_address),
          channel_status_(ChannelStatus::UNSELECTED),
          channel_selected_(TCA9548AChannel::INVALID),
          force_select_(force_select) {}

    void WriteToChannel(TCA9548AChannel channel,
                        const shared::i2c::Message& msg) override {

        std::cout << "Writing to channel " << std::to_string((uint8_t)channel) << std::endl;
        if (force_select_) {
            std::cout << "force select" << std::endl;
            ForceSelectChannel(channel);
        } else {
            std::cout << "soft select" << std::endl;
            SoftSelectChannel(channel);
        }
        std::cout << "channel: " << std::to_string((uint8_t) channel_status_) << " " << std::to_string((uint8_t) channel_selected_) << std::endl;
        std::cout << "writing: " << msg << std::endl;
        // Forward the message to selected channel
        i2c_bus_.Write(msg);
    }

    void ReadFromChannel(TCA9548AChannel channel,
                         shared::i2c::Message& msg) override {
        if (force_select_) {
            ForceSelectChannel(channel);
        } else {
            SoftSelectChannel(channel);
        }

        // Read from selected channel
        i2c_bus_.Read(msg);
    }

private:
    void ForceSelectChannel(TCA9548AChannel channel) {
        uint8_t channel_select = 1 << static_cast<uint8_t>(channel);
        uint8_t select_data[] = {channel_select};
        
        shared::i2c::Message select_msg(mux_address_, select_data,
                                        shared::i2c::MessageType::Write);
        
        std::cout << "channel select msg" << select_msg << std::endl;
        
        i2c_bus_.Write(select_msg);

        channel_status_ = ChannelStatus::SELECTED;
        channel_selected_ = channel;
    }

    void SoftSelectChannel(TCA9548AChannel channel) {
        std::cout << std::to_string((uint8_t) channel_selected_) << " " << std::to_string((uint8_t) channel) << std::endl;
        if (channel_selected_ != channel ||
            channel_status_ == ChannelStatus::UNSELECTED) {
            uint8_t channel_select = 1 << static_cast<uint8_t>(channel);
            uint8_t select_data[] = {channel_select};
            shared::i2c::Message select_msg(mux_address_, select_data,
                                            shared::i2c::MessageType::Write);
            std::cout << "channel select msg" << select_msg << std::endl;
            i2c_bus_.Write(select_msg);

            channel_status_ = ChannelStatus::SELECTED;
            channel_selected_ = channel;
        }
    }

    void DeselectChannel() {
        channel_status_ = ChannelStatus::UNSELECTED;
        channel_selected_ = TCA9548AChannel::INVALID;
    }

    ChannelStatus channel_status_;
    TCA9548AChannel channel_selected_;
    bool force_select_;
};

}  // namespace shared::device::ti
