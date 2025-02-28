using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Media.Animation;

namespace FoxHQ_installer_WPF
{
    public partial class MainWindow
    {
        private async partial Task CreateElement0()
        {
            // 渐渐显示文字或图片的 动画
            DoubleAnimation fadeIn = new DoubleAnimation
            {
                From = 0,
                To = 1,
                Duration = TimeSpan.FromSeconds(0.3),
                FillBehavior = FillBehavior.HoldEnd
            };

            // 添加 FoxHQ 安装程序 字样
            TextBlock Title = new TextBlock
            {
                Text = "FoxHQ 安装程序",
                HorizontalAlignment = HorizontalAlignment.Left,
                VerticalAlignment = VerticalAlignment.Top,
                Margin = new Thickness(20, 20, 0, 0),
                FontSize = 50,
                FontWeight = FontWeights.Light,

                Opacity = 0
            };
            Grid.Children.Add(Title);

            // 添加一个Label（第一个按钮：修改现有服务端）
            Label ModifyExistingServer = new Label
            {
                Background = new SolidColorBrush(Color.FromRgb(245, 245, 245)),
                BorderThickness = new Thickness(1),
                Width = 700,
                Height = 80,
                Opacity = 0,

                HorizontalAlignment = HorizontalAlignment.Left,
                VerticalAlignment = VerticalAlignment.Top,

                Margin = new Thickness(20, 100, 0, 0)
            };
            Grid.Children.Add(ModifyExistingServer);

            // 让文字渐渐显示在屏幕上
            Title.BeginAnimation(UIElement.OpacityProperty, fadeIn);

            // 让Label渐渐显示在屏幕上
            await Task.Delay(300);
            ModifyExistingServer.BeginAnimation(UIElement.OpacityProperty, fadeIn);
        }
    }
}
