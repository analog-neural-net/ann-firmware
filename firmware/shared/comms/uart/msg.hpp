#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

#pragma once

namespace shared::uart {

enum class MessageType : uint8_t {
    Transmit = 0,
    Receive = 1
};

template <MessageType msg_type>
struct Message {
    // Pure virtual template method that derived classes must implement
    template <size_t N>
    Message(uint8_t (&data)[N])
        : data_length_(N), data_(data), msg_type_(msg_type) {}

    // Delete default constructor
    Message() = delete;

    size_t DataLength() const {
        return data_length_;
    }

    uint8_t* Data() const {
        return data_;
    }

    // Pure virtual template method that derived classes must implement
    template <size_t N>
    bool SetData(const uint8_t (&new_data)[N]) {
        std::memcpy(data_, new_data, N);
        return true;
    }

    // Convert to string method
    std::string ToString() const {
        std::stringstream ss;

        // Format message type
        if (msg_type_ == MessageType::Transmit) {
            ss << "TX -> ";
        } else {
            ss << "RD <- ";
        }

        // Format data length
        ss << "(" << static_cast<int>(data_length_) << ")";

        // Format data
        for (size_t i = 0; i < data_length_; ++i) {
            ss << " " << std::uppercase << std::hex << std::setw(2)
               << std::setfill('0') << static_cast<int>(data_[i]);
        }

        return ss.str();
    }

private:
    uint8_t data_length_;
    uint8_t* data_;
    MessageType msg_type_;
};

}  // namespace shared::uart

// Operator overload for stream insertion
template <shared::uart::MessageType msg_type>
inline std::ostream& operator<<(std::ostream& os,
                                const shared::uart::Message<msg_type>& msg) {
    return os << msg.ToString();
}