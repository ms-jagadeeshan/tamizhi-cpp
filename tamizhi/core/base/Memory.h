#pragma once

#include <array>
#include <deque>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

#include "tamizhi/core/base/RawPointer.h"

// Shared Pointers.
template <typename T>
using tmzSP = std::shared_ptr<T>;

// Unique Pointers.
template <typename T>
using tmzUP = std::unique_ptr<T>;

// Vector of objections.
template <typename T>
using tmzCollection = std::vector<T>;

// Vector of shared pointers.
template <typename T>
using tmzSPCollection = std::vector<std::shared_ptr<T>>;

// Vector of unique pointers.
template <typename T>
using tmzUPCollection = std::vector<std::unique_ptr<T>>;

// Vector of raw pointers.
template <typename T>
using tmzRPCollection = std::vector<tmz::crRawPointer<T>>;

// Array
template <typename T, std::size_t N>
using tmzArray = std::array<T, N>;

template <typename T, std::size_t N>
using tmzRPArray = std::array<tmz::crRawPointer<T>, N>;

template <typename T, std::size_t N>
using tmzSPArray = std::array<std::shared_ptr<T>, N>;

template <typename T, std::size_t N>
using tmzUPArray = std::array<std::unique_ptr<T>, N>;

// Queue
template <typename T>
using tmzQueue = std::queue<T>;

template <typename T>
using tmzRPQueue = std::queue<tmz::crRawPointer<T>>;

template <typename T>
using tmzSPQueue = std::queue<std::shared_ptr<T>>;

template <typename T>
using tmzUPQueue = std::queue<std::unique_ptr<T>>;

// Ordered Maps.
template <typename T, typename Q>
using tmzMap = std::map<T, Q>;

template <typename T, typename Q>
using tmzUOMap = std::unordered_map<T, Q>;

template <typename T, typename Q>
using tmzRPMap = std::map<T, tmz::crRawPointer<Q>>;

template <typename T, typename Q>
using tmzSPMap = std::map<T, std::shared_ptr<Q>>;

template <typename T, typename Q>
using tmzUPMap = std::map<T, std::unique_ptr<Q>>;

// Unordered maps.
template <typename T, typename Q>
using tmzUnorderedMap = std::unordered_map<T, Q>;

template <typename T, typename Q>
using tmzRPUnorderedMap = std::unordered_map<T, tmz::crRawPointer<Q>>;

template <typename T, typename Q>
using tmzSPUnorderedMap = std::unordered_map<T, std::shared_ptr<Q>>;

template <typename T, typename Q>
using tmzUPUnorderedMap = std::unordered_map<T, std::unique_ptr<Q>>;

// Sets.
template <typename T>
using tmzSet = std::set<T>;

template <typename T>
using tmzRPSet = std::set<tmz::crRawPointer<T>>;

template <typename T>
using tmzSPSet = std::set<std::shared_ptr<T>>;

template <typename T>
using tmzUPSet = std::set<std::unique_ptr<T>>;

// Stack.
template <typename T>
using tmzStack = std::stack<T>;

template <typename T>
using tmzRPStack = std::stack<tmz::crRawPointer<T>>;

template <typename T>
using tmzSPStack = std::stack<std::shared_ptr<T>>;

template <typename T>
using tmzUPStack = std::stack<std::unique_ptr<T>>;
