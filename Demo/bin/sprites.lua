-- here's the spriteloading facility
-- be gentle with it
sprites =
{
    dude = {
        path = "gfx/dude.png",
        w = 10, h = 10,
    },

    girl = {
        {
            path = "gfx/action.png",
            x = 2, y = 3,
            w = 5, h = 6,
            color = 0xff232132,
            x_off = 10, y_off = 10,
        },
        {
            path = "gfx/action.png",
            x = 5, y = 5,
            w = 10, h = 10,
            x_off = 4, y_off = 4,
            frames = 5,
            fps = 50,
        },
    }
}

