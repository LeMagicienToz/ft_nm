// bss_symbols.c

int global_bss;         // Non initialisé → .bss → symbole global → B
static int static_bss;  // Non initialisé et static → .bss → symbole local → b

int main() {
    return 0;
}
