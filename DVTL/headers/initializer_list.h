#ifndef DVTL_INITIALIZER_LIST_H
#define DVTL_INITIALIZER_LIST_H

namespace DVTL
{
	template<typename T>
	class initializer_list {
    public:
        constexpr initializer_list() noexcept : First(nullptr), Last(nullptr) {}
        constexpr initializer_list(const T* First_arg, const T* Last_arg) noexcept : First(First_arg), Last(Last_arg) {}
        template<size_t N> constexpr initializer_list(const T(&arr_arg)[N]) noexcept : First(arr_arg), Last(arr_arg + N) {}

        constexpr const T* begin() const noexcept { return First; }
        constexpr const T* end() const noexcept { return Last; }
        constexpr size_t size() const noexcept { return static_cast<size_t>(Last - First); }
    private:
        const T* First;
        const T* Last;
	};
}

#endif // !DVTL_INITIALIZER_LIST_H