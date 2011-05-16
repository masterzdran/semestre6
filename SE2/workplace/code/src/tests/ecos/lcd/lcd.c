void lcd_init() {
/* Seleccionar os pinos de RESET E BACKLIGHT para o GPIO */
U32 pinsel = io_read_u32(LPC210X_SCB + LPC2XXX_PINSEL0);
io_write_u32(LPC210X_SCB + LPC2XXX_PINSEL0,
pinsel & ~(3 << BACKLIGHT_PIN * 2) & ~(3 << RESET_PIN * 2));
/* desactivar o sinal reset e backlight */
io_write_u32(LPC210X_GPIO + LPC2XXX_IOSET,
1 << BACKLIGHT_PIN | 1 << RESET_PIN);
/* e programá-los como saídas */
U32 iodir = io_read_u32(LPC210X_GPIO + LPC2XXX_IODIR);
io_write_u32(LPC210X_GPIO + LPC2XXX_IODIR,
iodir | 1 << BACKLIGHT_PIN | 1 << RESET_PIN);
/* executar reset */
io_write_u32(LPC210X_GPIO + LPC2XXX_IOCLR, 1 << RESET_PIN);
io_write_u32(LPC210X_GPIO + LPC2XXX_IOSET, 1 << RESET_PIN);
}
void lcd_backlight(int on) {
if (on)
io_write_u32(LPC210X_GPIO + LPC2XXX_IOSET, 1 << BACKLIGHT_PIN);
else
io_write_u32(LPC210X_GPIO + LPC2XXX_IOCLR, 1 << BACKLIGHT_PIN);
}

Spi_device spis[] = {
{
8, /* GPIO chip select position */
10, /* o sinal SCLK terá a frequência = PCLK / este valor */
0, /* modo SPI = 0;  cpol = 0, cpha = 0*/
9 /* number of bits per word */
}
};

static inline void write_command(U8 command) {
spi_write(spi, ~0x100 & command);
}
static inline void write_data(U8 data) {
spi_write(spi, 0x100 | data);
}


void lcd_init() {
...
spi_transaction_begin(spi);
write_command(DISCTL); /* display control */
write_data(0x00); /* P1: 0x00 = 2 divisions,
switching period=8 (default) */
write_data(32); /* P2: nlines/4 - 1 = 132/4 - 1 = 32) */
write_data(00); /* P3: 0x00 = no inversely highlighted lines */
write_command(COMSCN); /* COM scan */
write_data(1); /* P1: 0x01 = Scan 1->80, 160<-81 */
write_command(OSCON); /* Internal oscilator ON */
write_command(SLPOUT); /* sleep out */
write_command(VOLCTR); /* Voltage control (contrast setting) */
write_data(contrast); /* P1 = 32 volume value (experiment with this
value to get the best contrast) */
write_data(3); /* P2 = 3 resistance ratio
(only value that works) */
write_command(PWRCTR); /* Power control */
write_data(0x0f); /* reference voltage regulator on,
circuit voltage follower on, BOOST ON */
write_command(DATCTL); /* Data control */
write_data(0x00); /* P1: 0x00 = page address normal,
column address normal,
address scan in column direction */
write_data(0x00); /* P2: 0x00 = RGB sequence (default value) */
write_data(0x02); /* P3: 0x02 = Grayscale -> 16
(selects 12-bit color, type A) */
write_command(DISON); /* Display on */
spi_transaction_end(spi);
}

void lcd_draw_point(int x, int y, int color) {
spi_select(spi);
write_command(CASET); /* Column address set (command 0x2A) */
write_data(x);
write_data(x);
write_command(PASET); /* Page address set (command 0x2B) */
write_data(y);
write_data(y);
write_command(RAMWR); /* write memory */
write_data(color >> 4);
write_data((color & 0xf) << 4);
write_data(0);
write_command(NOP);
spi_unselect(spi);
}
void lcd_draw_hor_line(int x, int y, int  dx, int color) {
int i;
spi_select(spi);
write_command(CASET);
write_data(x);
write_data(x + dx - 1);
write_command(PASET);
write_data(y);
write_data(y);
write_command(RAMWR);
for (i = (dx + 1) / 2; i > 0; --i) {
write_data(color >> 4);
write_data(((color << 4) & 0xf0) | ((color >> 8) & 0xf) );
write_data(color);
}
write_command(NOP);
spi_unselect(spi);
}
void lcd_draw_ver_line(int x, int y, int  dy, int color) {
int i;
spi_select(spi);
write_command(CASET);
write_data(x);
write_data(x);
write_command(PASET);
write_data(y);
write_data(y + dy - 1);
write_command(RAMWR);
for (i = (dy + 1) / 2; i > 0; --i) {
write_data(color >> 4);
write_data(((color << 4) & 0xf0) | ((color >> 8) & 0xf) );
write_data(color);
}
write_command(NOP);
spi_unselect(spi);

}
void lcd_fill_rectangle(int x, int y, int dx, int dy, int color) {
int i;
spi_select(spi);
write_command(CASET);
write_data(x);
write_data(x + dx - 1);
write_command(PASET);
write_data(y);
write_data(y + dy - 1);
write_command(RAMWR);
for (i = (dx * dy + 1) / 2 + 1; i > 0; --i) {
write_data(color >> 4);
write_data(((color << 4) & 0xf0) | ((color >> 8) & 0xf) );
write_data(color);
}
write_command(NOP);
spi_unselect(spi);
}
void lcd_copy_rectangle(int x, int y, int dx, int dy, U8 * bitmap) {
int i;
spi_select(spi);
write_command(CASET);
write_data(x);
write_data(x + dx - 1);
write_command(PASET);
write_data(y);
write_data(y + dy - 1);
write_command(RAMWR);
for (i = (dx * dy + 1) / 2 + 1; i > 0; --i) {
write_data(*bitmap++);
}
write_command(NOP);
spi_unselect(spi);
}