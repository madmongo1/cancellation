//
// Copyright (c) 2021 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/cancellation
//

#ifndef CANCELLATION_AUTO_WEBSOCKET_HPP
#define CANCELLATION_AUTO_WEBSOCKET_HPP

#include "config.hpp"

#include <boost/beast/core/flat_buffer.hpp>

#include <span>
#include <string>

namespace program
{
struct websocket_message;

struct websocket_message_base
{
    bool
    is_binary() const
    {
        return type_ == type_binary;
    }

    bool
    is_text() const
    {
        return type_ == type_text;
    }

    std::string_view
    text() const
    {
        assert(is_text());
        auto d = buffer_.cdata();
        return std::string_view(static_cast< const char * >(d.data()),
                                d.size());
    }

    std::span< const unsigned char >
    binary() const
    {
        assert(is_binary());
        auto d = buffer_.cdata();
        auto p = static_cast< const unsigned char * >(d.data());
        auto s = d.size();
        return std::span< const unsigned char >(p, s);
    }

  protected:
    boost::beast::flat_buffer &
    buffer()
    {
        return buffer_;
    }

    boost::beast::flat_buffer const &
    buffer() const
    {
        return buffer_;
    }

  private:
    boost::beast::flat_buffer buffer_;
    enum type
    {
        type_text,
        type_binary
    } type_ = type_text;
};

struct mutable_websocket_message : public websocket_message_base
{
    mutable_websocket_message(std::size_t initial_size = 1024 * 1024)
    : websocket_message_base()
    {
        buffer().reserve(initial_size);
    }
};

struct websocket_message : private websocket_message_base
{
    websocket_message(mutable_websocket_message &&source)
    : websocket_message_base(std::move(source))
    {
    }

    using websocket_message_base::binary;
    using websocket_message_base::is_binary;
    using websocket_message_base::is_text;
    using websocket_message_base::text;
};

struct auto_websocket_event
{
    using variant_type = variant< error_code, websocket_message >;

    auto_websocket_event(error_code ec = error_code(errc::invalid_argument,
                                                    generic_category()))
    : var_(ec)
    {
    }

    auto_websocket_event(websocket_message &&msg)
    : var_(std::move(msg))
    {
    }

    bool
    is_error() const
    {
        return holds_alternative< error_code >(var_);
    }
    bool
    is_message() const
    {
        return holds_alternative< websocket_message >(var_);
    }

    error_code const &
    error() const
    {
        assert(is_error());
        return get< error_code >(var_);
    }

    websocket_message const &
    message() const
    {
        assert(is_error());
        return get< websocket_message >(var_);
    }

    variant_type &
    as_variant()
    {
        return var_;
    }

    variant_type const &
    as_variant() const
    {
        return var_;
    }

  private:
    variant_type var_;
};

/// @brief A websocket which auto-connects until stopped
struct auto_websocket
{
    auto_websocket(std::string url);
};

}   // namespace program

#endif   // CANCELLATION_AUTO_WEBSOCKET_HPP
