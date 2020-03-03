# 关于Qt顶级窗口装饰的几个方法

## 编译依赖
- qt5-default
- libqt5x11extras5-dev
- qtbase5-private-dev

## Qt::FrameLessWindowHint
这个大家都比较熟悉，我就不多做介绍了

## Mutter,ukwm等Gtk阵营窗口管理器的decoration协议
_MOTIF_WM_HINTS是Gtk阵营窗口管理器装饰窗口的协议，与我们一般认为的窗口管理器修饰不同，它有几种装饰窗口的类型可选，我们这里选择MWM_DECOR_BORDER和MWM_DECOR_ALL作为示例展示，注意KWin下这个设置没有效果。

另外虽然KWin不支持这个操作，但是这并不代表KWin无法实现类似的行为，因为KWin也支持gtk窗口的csd（客户端渲染），比如在plasma下运行nautilus，它仍然可以以自定义标题栏的形式在kwin下渲染，同时获取kwin的缩放句柄支持，这说明kwin是对csd进行过适配的。可惜我暂时没有找到qt相关的接口，也不确定它是不是只对gtk应用有效，目前的线索只有_GTK_FRAME_EXTENTS这个协议。

## X11标准协议实现窗口拖拽
这段代码改进自轩哥曾经在邮件中提到的无边框窗口的缩放问题的解决方案，主要区别在于我把它通过qt的事件过滤器以钩子的形式实现了，这一块借鉴的是kde社区的主题的做法。

## QWidgetResizeHandler
这是qt private api提供的类，用它实现无边框窗口的拖拽和缩放是比较方便的，问题就是它不支持半屏缩放等与窗口管理器结合的功能，一般是与第三项联用，限定窗口拖拽触发的范围，只使用它的缩放功能。