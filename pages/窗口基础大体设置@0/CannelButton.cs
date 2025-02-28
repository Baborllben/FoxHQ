using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace FoxHQ_installer_WPF
{
    public partial class MainWindow
    {
        // 取消按钮，点击关闭窗口
        partial void Cancel_Click(object sender, RoutedEventArgs e)
        {
            // 创建一个透明度动画，不透明 到 透明
            DoubleAnimation fadeOut = new DoubleAnimation
            {
                To = 0,                                 // 目标透明度
                Duration = TimeSpan.FromSeconds(0.3),   // 动画持续时间 0.3 秒
                FillBehavior = FillBehavior.Stop        // 动画结束后回到初始状态
            };

        // 监听动画完成事件，动画完成后关闭窗口
        fadeOut.Completed += (s, e) => this.Close();

            // 应用动画到窗口
            this.BeginAnimation(Window.OpacityProperty, fadeOut);
        }

        partial void CancelButton_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e)
        {
            CancelButton_AnimateBackground(CancelButton, Colors.LightBlue, Colors.White, 0.5);
        }

        // 封装的动画方法
        private void CancelButton_AnimateBackground(Button button, Color fromColor, Color toColor, double durationInSeconds)
        {
            // 创建颜色动画
            ColorAnimation colorAnimation = new ColorAnimation
            {
                From = fromColor,
                To = toColor,
                Duration = TimeSpan.FromSeconds(durationInSeconds)
            };

            // 创建新的 SolidColorBrush 以应用动画
            SolidColorBrush brush = new SolidColorBrush(fromColor);
            button.Background = brush; // 设置按钮背景

            // 应用动画到 SolidColorBrush
            brush.BeginAnimation(SolidColorBrush.ColorProperty, colorAnimation);
        }
    }
}
