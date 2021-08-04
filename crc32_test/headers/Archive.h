#ifndef CRC32_TEST_ARCHIVE_H
#define CRC32_TEST_ARCHIVE_H

#include <utility>

template<class _Impl>
class Archive {
public:
    using Impl = _Impl;

//    template<class T>
//    Archive operator<<(const T &t) {
//        return *this;
//    }

    template<class T>
    Impl& operator&(T&& t) {
        static_assert( std::is_base_of_v<Archive, _Impl> );

        auto& self = static_cast<Impl&>(*this);

        if (not m_failed) {
            m_failed |= self.apply(std::forward<T>(t)) == false;
        }
        return self;
    }

    explicit operator bool() const { return not m_failed; }

    virtual void reset() {
        m_failed = false;
    }

protected:
    Archive() = default;

    /** @returns true when application succeeded */
    template<class T>
    bool apply(T&&)
    {
        return false;
    }

    bool m_failed = false;
};


#endif //CRC32_TEST_ARCHIVE_H