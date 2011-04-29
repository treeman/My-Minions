#pragma once

namespace Tree
{
    class DrawnLazy {
    public:
        DrawnLazy();
        virtual ~DrawnLazy();

        // one function to render it lazily
        void Draw();
        // foce it to render whatsoever
        void ForceDraw();

        // flag for us to redraw when we call draw
        void Redraw();
        bool WillRedraw();
    protected:
        // called when Redraw is called
        virtual void NewRedraw() { }

        // function to actually draw something
        virtual void Render() = 0;

        bool need_to_redraw;
    };
}

