/*
 * Copyright (C) 2015 Niek Linnenbank
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Set the priority of a process.");
    parser().registerPositional("PRIO", "The priority to set");
    parser().registerPositional("PID", "The process ID to wait on");
}

Renice::Result Renice::exec()
{
    int priority = atoi(arguments().get("PRIO"));
    int pid = atoi(arguments().get("PID"));

    const ProcessClient process;

    if (ProcessCtl(pid, SetPriority, priority) == API::Success) {
        return Success;
    } else {
        return InvalidArgument;
    }    
}
