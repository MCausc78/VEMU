from pyvemu import vga

class VGADisplay:
    def __init__(self: VGADisplay):
        self._column = 0
        self._row = 0
        self._color = 0x00
        self._buffer = [0] * 2080
    def reset_color(self: VGADisplay) -> VGADisplay:
        self.set_color(vga.entry_color(vga.VGA_COLOR_WHITE, vga.VGA_COLOR_BLACK))
        return self
    def get_row(self: VGADisplay) -> int:
        return self._row
    def get_column(self: VGADisplay) -> int:
        return self._column
    def get_row(self: VGADisplay) -> int:
        return self._row
    def set_row(self: VGADisplay, row: int) -> VGADisplay:
        assert row >= 0 and row < vga.VGA_HEIGHT
        self._row = row
        return self
    def set_column(self: VGADisplay, column: int) -> VGADisplay:
        assert column >= 0 and column < vga.VGA_WIDTH
        self._column = column
        return self
    def set_color(self: VGADisplay, color: int) -> VGADisplay:
        assert color >= 0x00 and color <= 0xFF
        self._color = color
        return self
    def clear(self: VGADisplay) -> VGADisplay:
        self.set_row(0)
        self.set_col(0)
        entry = vga.entry(' ', self.get_color())
        self._buffer = [entry] * 2080
        return self
    def scroll(self: VGADisplay) -> VGADisplay:
        raise NotImplementedError()
        return self
    def put_char_at(self: VGADisplay, character: str, color: int, x: int, y: int) -> VGADisplay:
        assert (((len(str) == 1) and (color >= 0x00 and color <= 0xFF)) and ((x >= 0 and x < vga.VGA_WIDTH) and (y >= 0 and x < vga.VGA_HEIGHT)))
        if character == '\a' or character == '\b' or character == '\f' or character == '\n' or character == '\r':
            return self
        self._buffer[ vga.get_index(x, y) ] = vga.entry(
            character=character,
            color=color)
        return self
    def put_char(self: VGADisplay, character: str) -> VGADisplay:
        if not (len(character) == 1):
            raise ValueError("expected single character, got %s" % character))
        if (self._column := self._column + 1) == vga.VGA_WIDTH:
            self.set_column(0)
            if (self._row := self._row + 1) == vga.VGA_HEIGHT:
                tty.set_row(0)
        if character == '\a':
            self._column -= 1
        elif character == '\b':
            if self._column > 1:
                self._column -= 2
        elif character == '\f':
            self.clear()
        elif character == '\n':
            self.set_column(0)
            self._row += 1
            if self._row == vga.VGA_HEIGHT:
                self.set_row(0)
        elif character == '\r':
            self.set_column(0)
        elif character == '\t':
            for _ in range(4):
                self.put_char(' ')
        return self
    def put_colored_char(self: VGADisplay, character: str, color: int) -> VGADisplay:
        assert ((len(character) == 1) and (color >= 0x00 and color <= 0xFF))
        oldColor = self.color | 0
        self.set_color(color)
        self.put_char(character)
        self.set_color(oldColor)
        return self