/// @file default_delete.h
/// @data 07/03/2014 11:35:53
/// @author Ambroise Leclerc
/// @brief Default destruction policy used by std::unique_ptr when no deleter is specified.
//
// Embedded Template Library
// Copyright (c) 2014, Ambroise Leclerc
//   All rights reserved.
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in
//     the documentation and/or other materials provided with the
//     distribution.
//   * Neither the name of the copyright holders nor the names of
//     contributors may be used to endorse or promote products derived
//     from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.

#pragma once

namespace std {
  
template<typename T> struct default_delete {
    /// Default constructor.
    constexpr default_delete() noexcept = default;
  
    /// Converting constructor from another type.
    template<typename T2> constexpr default_delete(const default_delete<T2>&) noexcept { }
    
    void operator()(T* pointer) { delete pointer; }
};

/// std::default_delete specialization for arrays
template<typename T> struct default_delete<T[]> {
    /// Default constructor.
    constexpr default_delete() noexcept = default;
  
    /// Converting constructor from another type.
    template<typename T2> constexpr default_delete(const default_delete<T2[]>&) noexcept { }
    
    void operator()(T* pointer) { delete[] pointer; }
};

} // namespace std
