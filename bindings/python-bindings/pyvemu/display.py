from pyvemu import vga

class VGADisplay:
    def __init__(self):
        self._column = 0
        self._row = 0
        self._color = 0x00
        self._buffer = [0] * 2080
    def reset_color(self):
        self.set_color(vga.entry_color(vga.VGA_COLOR_WHITE, vga.VGA_COLOR_BLACK))
        return self
    def get_buffer(self) -> list:
        return self._buffer
    def get_color(self) -> int:
        return self._color
    def get_column(self) -> int:
        return self._column
    def get_row(self) -> int:
        return self._row
    def set_row(self, row: int):
        assert row >= 0 and row < vga.VGA_HEIGHT
        self._row = row
        return self
    def set_column(self, column: int):
        assert column >= 0 and column < vga.VGA_WIDTH
        self._column = column
        return self
    def set_color(self, color: int):
        assert color >= 0x00 and color <= 0xFF
        self._color = color
        return self
    def clear(self):
        self.set_row(0)
        self.set_col(0)
        entry = vga.entry(' ', self.get_color())
        self._buffer = [entry] * 2080
        return self
    def scroll(self):
        raise NotImplementedError()
        return self
    def put_char_at(self, character: str, color: int, x: int, y: int):
        if not (len(character) == 1):
            raise ValueError("expected single character, got '%s'" % character)
        assert ((color >= 0x00 and color <= 0xFF) and ((x >= 0 and x < vga.VGA_WIDTH) and (y >= 0 and x < vga.VGA_HEIGHT)))
        if character == '\a' or character == '\b' or character == '\f' or character == '\n' or character == '\r':
            return self
        self._buffer[ vga.get_index(x, y) ] = vga.entry(
            character=character,
            color=color)
        return self
    def put_char(self, character: str):
        if not (len(character) == 1):
            raise ValueError("expected single character, got '%s'" % character)
        self.put_char_at(character, self._color, this._column, this._row)
        self._column += 1
        if self._column == vga.VGA_WIDTH:
            self.set_column(0)
            self._row += 1
            if self._row == vga.VGA_HEIGHT:
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
    def put_colored_char(self, character: str, color: int):
        assert ((len(character) == 1) and (color >= 0x00 and color <= 0xFF))
        oldColor = self.color | 0
        self.set_color(color)
        self.put_char(character)
        self.set_color(oldColor)
        return self
    def print(self, string: str):
        for c in string:
            self.put_char(c)
