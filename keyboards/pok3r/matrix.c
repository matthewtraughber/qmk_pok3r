/*
 * Copyright (c) 2018 Charlie Waters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"

#include "pok3r.h"

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

static inline void init_row(ioportid_t portid, ioportmask_t portmask, size_t portoffset) {
    palWriteGroup(portid, portmask, portoffset, portmask);
    palSetGroupMode(portid, portmask, portoffset, PAL_MODE_OUTPUT_PUSHPULL | PAL_MODE_HT32_AF(AFIO_GPIO));
}

static inline void init_col(ioportid_t portid, ioportmask_t portmask, size_t portoffset) {
    palSetGroupMode(portid, portmask, portoffset, PAL_MODE_INPUT_PULLUP | PAL_MODE_HT32_AF(AFIO_GPIO));
}

void matrix_init(void) {
    // Matrix "columns" are pulsed
    init_row(GPIO_A, 0x0078, 0);    // A3,A4,A5,A6  COL1,COL2,COL3,COL4
    init_row(GPIO_B, 0x0800, 0);    // B11          COL5
    init_row(GPIO_C, 0xE000, 0);    // C13,C14,C15  COL6,COL7,COL8

    // Matrix "rows" are inputs
    init_col(GPIO_A, 0x8800, 0);    // A11,A15      ROW3,ROW5
    init_col(GPIO_B, 0x003A, 0);    // B1,B3,B4,B5  ROW7,ROW4,ROW6,ROW8
    init_col(GPIO_C, 0x0120, 0);    // C5,C8        ROW2,ROW9
    init_col(GPIO_D, 0x0001, 0);    // D0           ROW1

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    // SPI flash
    //palSetGroupMode(GPIO_B, 0x7, 7, PAL_MODE_HT32_AF(AFIO_SPI)); /* SPI1 */
    //palSetLine(LINE_NORCE);
    //palSetLineMode(LINE_NORCE, PAL_MODE_OUTPUT_PUSHPULL); /* CE/CS */

    matrix_init_quantum();
}

static matrix_row_t read_columns(void) {
    return palReadLine(LINE_ROW1) |
        (palReadLine(LINE_ROW2) << 1) |
        (palReadLine(LINE_ROW3) << 2) |
        (palReadLine(LINE_ROW4) << 3) |
        (palReadLine(LINE_ROW5) << 4) |
        (palReadLine(LINE_ROW6) << 5) |
        (palReadLine(LINE_ROW7) << 6) |
        (palReadLine(LINE_ROW8) << 7) |
        (palReadLine(LINE_ROW9) << 8);
}

static const ioline_t row_list[MATRIX_ROWS] = {
    LINE_COL1,
    LINE_COL2,
    LINE_COL3,
    LINE_COL4,
    LINE_COL5,
    LINE_COL6,
    LINE_COL7,
    LINE_COL8,
};

uint8_t matrix_scan(void) {
    // scan each row
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data;

        palSetLine(row_list[row]);
        wait_us(20);
        data = read_columns();
        palClearLine(row_list[row]);

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1 << col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("% 3u ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col)) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
}

