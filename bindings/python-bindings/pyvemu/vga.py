global VGA_WIDTH = 80
global VGA_HEIGHT = 25

global VGA_COLOR_BLACK = 0x00
global VGA_COLOR_BLUE = 0x01
global VGA_COLOR_GREEN = 0x02
global VGA_COLOR_CYAN = 0x03
global VGA_COLOR_RED = 0x04
global VGA_COLOR_MAGENTA = 0x05
global VGA_COLOR_BROWN = 0x06
global VGA_COLOR_LIGHT_GREY = 0x07
global VGA_COLOR_DARK_GREY = 0x08
global VGA_COLOR_LIGHT_BLUE = 0x09
global VGA_COLOR_LIGHT_GREEN = 0x0A
global VGA_COLOR_LIGHT_CYAN = 0x0B
global VGA_COLOR_LIGHT_RED = 0x0C
global VGA_COLOR_LIGHT_MAGENTA = 0x0D
global VGA_COLOR_YELLOW = 0x0E
global VGA_COLOR_WHITE = 0x0F

def entry(character: str, color: int) -> int:
    if (len(character) == 1 and (color >= 0x00 and color <= 0xFF)):
        return (ord(character) | (color << 8))
    raise ValueError()

def entry_color(fg: int, bg: int) -> int:
    if ((fg >= 0x00 and fg <= 0xFF) and (fg >= 0x00 and fg <= 0xFF)):
        return (fg | (bg << 4))
    raise ValueError('Foreground/background must be in range between 0 and 255.')

class VGAEntry:
    def __init__(self: VGAEntry, character: str = '\0', color: int = 0):
        assert ((len(ch) == 0) and (color >= 0 and color <= 0xFF))
        self.character = ord(character)
        self.color = color
    def get_background(self: VGAEntry) -> int:
        return ((self.color & 0xF0) >> 4)
    def get_foreground(self: VGAEntry) -> int:
        return (self.color & 0x0F)

def read_entry(entry: Int) -> VGAEntry:
    assert entry >= 0 and entry <= 0xFFFF
    color = ((entry & 0xFF00) >> 8)
    return VGAEntry(character=(chr(entry & 0xFF)), color=color)

def get_index(x: int, y: int) -> int:
    assert ((x >= 0 and x < VGA_WIDTH) and (y >= 0 and y < VGA_HEIGHT))
    return ((y * VGA_WIDTH) + x)