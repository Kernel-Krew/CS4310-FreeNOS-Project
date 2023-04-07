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

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

// Constructor for Scheduler class
Scheduler::Scheduler()
{
    DEBUG("");
}

/**
 * Returns total number of processes in all priority levels
 * calculate total number of processes in the system
*/
Size Scheduler::count() const
{
    return m_ml5_queue.count() + m_ml4_queue.count() + m_ml3_queue.count() + m_ml2_queue.count() + m_ml1_queue.count();
}

/**
 * Adds process to correct queue based on priority
 * @param proc process to add to queue
 * @param ignoreState boolean to ignore state of process
 * @returns Success if process succefully added to queue, Invalid Argument
 * otherwise
 */
Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    // checks if process is in Ready State, and whether to ignore state
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }
    
    // Adds process to queue based on priority level
        switch (proc->getPriority())
    {
    case 1:
        m_ml1_queue.push(proc);
        break;
    case 2:
        m_ml2_queue.push(proc);
        break;
    case 3:
        m_ml3_queue.push(proc);
        break;
    case 4:
        m_ml4_queue.push(proc);
        break;
    case 5:
        m_ml5_queue.push(proc);
        break;
    default:
        m_ml3_queue.push(proc);
        break;
    }

    return Success;
}
/**
 * Removes a process from the queue
 * @param proc process to remove from queue
 * @param ignoreState boolean to ignore state of process
 * @returns success if process successfully removed from queue,
 * otherwise returns invalid argument.
*/
Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    Size count = m_ml5_queue.count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_ml5_queue.pop();

        if (p == proc)
            return Success;
        else
            m_ml5_queue.push(p);
    }


    count = m_ml4_queue.count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_ml4_queue.pop();

        if (p == proc)
            return Success;
        else
            m_ml4_queue.push(p);
    }

    count = m_ml3_queue.count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_ml3_queue.pop();

        if (p == proc)
            return Success;
        else
            m_ml3_queue.push(p);
    }

    count = m_ml2_queue.count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_ml2_queue.pop();

        if (p == proc)
            return Success;
        else
            m_ml2_queue.push(p);
    }

    count = m_ml1_queue.count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_ml1_queue.pop();

        if (p == proc)
            return Success;
        else
            m_ml1_queue.push(p);
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

/**
 * Selects next process to be run based on priority level queues
 * @return pointer to next process or Null if no processes left to run
*/
Process * Scheduler::select()
{
    if (m_ml5_queue.count() > 0)
    {
        Process *p = m_ml5_queue.pop();
        m_ml5_queue.push(p);
        return p;
    }
    if (m_ml4_queue.count() > 0)
    {
        Process *p = m_ml4_queue.pop();
        m_ml4_queue.push(p);
        return p;
    }
    if (m_ml3_queue.count() > 0)
    {
        Process *p = m_ml3_queue.pop();
        m_ml3_queue.push(p);
        return p;
    }
    if (m_ml2_queue.count() > 0)
    {
        Process *p = m_ml2_queue.pop();
        m_ml2_queue.push(p);
        return p;
    }
    if (m_ml1_queue.count() > 0)
    {
        Process *p = m_ml1_queue.pop();
        m_ml1_queue.push(p);
        return p;
    }

    return (Process *) NULL;
}
