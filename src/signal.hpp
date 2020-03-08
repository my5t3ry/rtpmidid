/**
 * Real Time Protocol Music Instrument Digital Interface Daemon
 * Copyright (C) 2019 David Moreno Montero <dmoreno@coralbits.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <functional>
#include <vector>

template<typename... Args>
class signal_t {
public:
    int connect(std::function<void(Args...)> const &f) {
        auto cid = max_id++;
        slots[cid]=std::move(f);
        return cid;
    }

    void disconnect(int id){
        slots.erase(id);
    }

    void operator()(Args... args){
        for (auto const &f: slots){
            f(std::forward<Args>(args)...);
        }
    }
private:
    int max_id = 0;
    std::vector<std::function<void(Args...)>> slots;
};
