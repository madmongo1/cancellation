//
// Copyright (c) 2021 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/cancellation
//

#ifndef CANCELLATION_CONFIG_HPP
#define CANCELLATION_CONFIG_HPP

#include <boost/asio.hpp>
#include <boost/system/errc.hpp>
#include <boost/system/error_code.hpp>
#include <boost/variant2/variant.hpp>

namespace program
{
namespace asio = boost::asio;
using boost::system::error_code;
using boost::system::system_category;
using boost::system::generic_category;
namespace errc = boost::system::errc;
using boost::variant2::variant;

}   // namespace program

#endif   // CANCELLATION_CONFIG_HPP
