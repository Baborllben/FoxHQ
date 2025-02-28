using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Animation;

namespace FoxHQ_installer_WPF
{
    public partial class MainWindow
    {
        private async partial Task RemoveLogo()
        {
            // 消失动画
            DoubleAnimation fadeOut = new DoubleAnimation
            {
                From = 1,
                To = 0,
                Duration = TimeSpan.FromSeconds(1),
                FillBehavior = FillBehavior.HoldEnd
            };

            // 文字和LOGO全部消失
            TEXT_Fotailx.BeginAnimation(UIElement.OpacityProperty, fadeOut);
            LOGO.BeginAnimation(UIElement.OpacityProperty, fadeOut);

            // 等待文字和LOGO消失后
            await Task.Delay(1200);
            // 删除这两个控件
            Grid.Children.Remove(TEXT_Fotailx);
            Grid.Children.Remove(LOGO);
        }
    }
}