#pragma once

namespace bw
{
    class IReleasable
    {
    public:
        virtual void release() = 0;
    };
}
