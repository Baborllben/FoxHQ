using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media.Animation;

namespace FoxHQ_installer_WPF
{
    public partial class MainWindow
    {
        public async partial void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // 窗口加载时执行渐显动画
            Window_Fade_In();

            // 先等 1 秒
            await Task.Delay(1000);
            // 窗口加载时显示 LOGO
            await ShowLogo();

            // 等待 ShowLogo()执行完成 和 1s
            await Task.Delay(1000);
            // 在LOGO显示后移除LOGO
            await RemoveLogo();

            // 创建主界面
            await CreateElement0();
        }
        private void Window_Fade_In()
        {
            // 创建一个透明度动画，从 不透明 到 可见
            DoubleAnimation fadeIn = new DoubleAnimation
            {
                From = 0,                               // 起始透明度
                To = 1,                                 // 目标透明度
                Duration = TimeSpan.FromSeconds(0.3),   // 动画持续时间 0.3 秒
                FillBehavior = FillBehavior.HoldEnd     // 结束时保持最终状态
            };

            // 应用动画到窗口
            this.BeginAnimation(Window.OpacityProperty, fadeIn);
        }
    }
}
