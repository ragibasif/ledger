/*
 * File: main.c
 * Author: Ragib Asif
 * Email: ragib.asif30@myhunter.cuny.edu
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 *
 */

#include "ledger.h"

void ledger_demo(void) {
    int port = 8080;
    size_t i = 32;
    char *filename = "output.txt";
    l_init(NULL);
    INFO("Server running on port %d.", port);
    WARN("Low memory detected.");
    DEBUG("Loop iteration: %u", i);
    ERROR("File not found - %s.", filename);
    l_fin();
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    ledger_demo();
    return 0;
}
