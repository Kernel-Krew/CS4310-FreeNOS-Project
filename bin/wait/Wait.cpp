/*
 * Copyright (C) 2009 Niek Linnenbank
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("This  function takes a numeric argument, which is the process-id to wait for.");
    parser().registerPositional("PID", "The process ID to wait on");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid = 0;

    // Get PID from arguments
    if ((pid = atoi(arguments().get("PID"))) < 0)
    {
        ERROR("invalid PID `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }

    // Wait for process to complete
    // if (sleep(sec) != 0)
    // {
    //     ERROR("failed to sleep: " << strerror(errno));
    //     return IOError;
    // }

    // Done
    return Success;
}
