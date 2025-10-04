#include <cstdint>
#include <span>

typedef void (*void_func_ptr)(void);

void error_handler()
{
    while (true)
        ;
}

extern "C" void reset_handler()
{
    extern void __libc_init_array();
    extern void __libc_fini_array();

    extern uint32_t _sdata;
    extern uint32_t _edata;
    extern uint32_t _sidata;
    extern uint32_t _sbss;
    extern uint32_t _ebss;

    std::span<uint32_t> const data_ram(&_sdata, &_edata);
    std::span<uint32_t const> const data_rom(&_sidata, data_ram.size());
    std::span<uint32_t> bss(&_sbss, &_ebss);

    system_init();

    std::copy(data_rom.begin(), data_rom.end(), data_ram.begin());
    std::fill(bss.begin(), bss.end(), 0);

    __libc_init_array();

    main();

    __libc_fini_array();

    error_handler();
}

// fill interrupt vector
constexpr __attribute__((section(.isr_vector))) std::array<void_func_ptr, 100> isr_vector_table = [] {
    std::array<void_func_ptr, 100> a;
    a[reset] = reset_handler;
    a[nmi] = nmi_handler;
    a[hardfault] = hardfault_handler;
    a[systick] = systick_handler;

    return a;
}();

// stack pointer top
extern uint32_t _estack;
extern "C" constexpr uint32_t *__attribute((section(".stack_top_ptr"))) stack_top_ptr = &_estack;
