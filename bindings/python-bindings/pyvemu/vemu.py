from pyvemu import display, vga

class VEMU:
    def __init__(self):
        self._display = display.VGADisplay()
    def get_display(self) -> display.VGADisplay:
        return self._display
    def set_display(self, newDisplay: display.VGADisplay):
        self._display = newDisplay
        return self
    def save(self, to: str):
        with open(to, 'wb') as f:
            buf = self._display.get_buffer()
            for y in range(vga.VGA_HEIGHT - 1):
                for x in range(vga.VGA_WIDTH - 1):
                    e = vga.read_entry( buf[ vga.get_index(x, y) ] )
                    f.write((f'{chr(e.color)}{chr(e.character)}').encode())
                # f.write(b'\0\0')
        return self