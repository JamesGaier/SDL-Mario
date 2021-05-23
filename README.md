![alternative text](http://www.plantuml.com/plantuml/proxy?cache=no&src=http://www.plantuml.com/plantuml/png/XLFTZjCy4BtFKrZwf4_fDhr1N5LHjU8710iIsbPmMRdnR6lXs94zwJPQbcV7zZZPa0sGA_kS-Japnxbso2ssjSgoMz02B3yeO5Uh5ViArOifjeDBvZ-f4UmThu2D-8UC-U-_UjyO9r4QpTPK8y7IROsImgELqGxPmHWLkQMDHNA1dhjJXkF27yv6YkmnozXhetpQ8E4MAXmf6EYnWeDfjP3w-CfSs3fcKAEs4HpX3ur2sDFWMQMuSp4trLsTmQBp2Gx5UisjvLqPGWlsSXFoKqQ0ojqc9IrtxD8VkX0rabl-yCs-ADw1JNkUmaDHklP2wdrbf0vIMktaKOFeySRZE4T8zx6j6xyIpz7Y2LVo37FnF13Zs2L9o2Vc5WpXWgqDiUyihy4LxFds5nEV9zkVc3FZ3MtXWsxQmOqJrqB13NGHpU4CEjYwVVDf_pQS__-zEeN_FPPwlUSrlJIQUBXJ-rvBH0S_cXWwF8w6IrjIUa68QSBIk4hePjDdtak1fna3JY2F9vmXKAA2lf53wnVzL4iBSvy6-nOlLptdMlfTYDpIBR4F3ZdAwb5gVz0eEO98tey7z9s6ru-cbbKP8cYIvS-ma3mP7Sz9AFtjOxa5cmvTi6VZBlxnnqvUr3pz7RhFlCaNWugR20INhtrcMwjV)
```plantuml


@startuml

Renderable *-- Vec2
Renderable *-- Tex



interface Renderable {
    #m_position : Vec2
    #m_isSolid : const bool
    +render(dt : float) : void
}

 Collidable *-- Rect

interface Collidable {
    #m_boundingBox : Rect
    +update(dt : float) : void
}

Rect *-- Vec2

class Rect {
    -verts : std::array<Vec2, 4>
}


class Vec2<T> {
    +T x
    +T y
}

Collidable <|-- Player
Renderable <|-- Player


class Player {
    -m_coins : unsigned
    -m_points : unsigned
    -m_isJumping : bool
    -m_lives : unsigned
    -m_alive : bool
    +Player(position : Vec2, texture : Frames, boundingBox : Rect)
    +render(dt: float) : void
    +update(dt: float) : void
}

class Input {
    -handleKeyInput(event : SDL_Event&) : void
    +handleInput(event : SDL_Event&) : void
}

Game *-- Player
Game *-- Input

class Game {
    -m_players : std::pair<Player, std::optional<Player>>
    -m_width : unsigned
    -m_height : unsigned
    -m_title : std::string
    -m_window : SDL_Window*
    -m_surface : SDL_Surface*
    -{static}instantiated : bool
    -m_playing : std::atomic<bool>
    +~Game()
    +Game(title : const std::string, width : unsigned, height : unsigned)
    +update(dt : float) : void
    +render(dt : float) : void
    +keyMap() : const KeyMap
}

@enduml
```
