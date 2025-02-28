using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace FoxHQ_installer_WPF
{
    public partial class MainWindow
    {
        private async partial Task ShowLogo()
        {
            // 图片变可见（原先不可见）
            DoubleAnimation fadeIn = new DoubleAnimation
            {
                From = 0,
                To = 1,
                Duration = TimeSpan.FromSeconds(0.3),
                FillBehavior = FillBehavior.HoldEnd
            };
            // 应用动画
            LOGO.BeginAnimation(UIElement.OpacityProperty, fadeIn);

            // 等 0.5 秒
            await Task.Delay(500);
            // 创建移动动画
            DoubleAnimation moveAnimation = new DoubleAnimation
            {
                To = -20,
                Duration = TimeSpan.FromSeconds(0.3),
                FillBehavior = FillBehavior.HoldEnd,
                EasingFunction = new QuadraticEase() { EasingMode = EasingMode.EaseOut } // 平滑效果
            };
            // 应用动画
            LOGO_MoveTransform.BeginAnimation(TranslateTransform.YProperty, moveAnimation);

            // LOGO文字变可见
            TEXT_Fotailx.BeginAnimation(UIElement.OpacityProperty, fadeIn);

            // 再再等 0.5 秒
            await Task.Delay(500);
            // 文字消失
            DoubleAnimation fadeOut = new DoubleAnimation
            {
                From = 1,
                To = 0,
                Duration = TimeSpan.FromSeconds(0.3),
                FillBehavior = FillBehavior.HoldEnd
            };
            // 应用动画
            TEXT_Fotailx.BeginAnimation(UIElement.OpacityProperty, fadeOut);

            // 再再等 0.3 秒
            await Task.Delay(300);
            // 更改文字内容为 by 狐不像
            TEXT_Fotailx.Text = "by 狐不像";
            TEXT_Fotailx.Width = 180;
            TEXT_Fotailx.Margin = new Thickness(0, 0, 5, 189);
            TEXT_Fotailx.FontSize = 24;
            
            // 再再再等 0.5 秒
            await Task.Delay(500);
            // 文字又出现
            TEXT_Fotailx.BeginAnimation(UIElement.OpacityProperty, fadeIn);
        }
    }
}
