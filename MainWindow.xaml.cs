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
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            // 设置程序图标
            this.Icon = new BitmapImage(new Uri("pack://application:,,,/Resources/favicon.ico"));

            /// 启动环节
            /// 启动环节 END
        }

        /// 窗口基础大体设置
        public partial void Window_Loaded(object sender, RoutedEventArgs e);   // 窗口加载时执行的函数
        partial void MoveWindow(object sender, MouseButtonEventArgs e); // 让用户可以拖动窗口
        partial void Cancel_Click(object sender, RoutedEventArgs e);    // 取消按钮，点击关闭窗口
        partial void CancelButton_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e); // 鼠标移出时，背景渐变回白色
        /// 窗口基础大体设置 END
        
        /// 加载页面（Logo页面）
        private partial Task ShowLogo();    // 在程序打开的时候展示**团队的Logo**和制作人信息
        private partial Task RemoveLogo();    // 显示**团队Logo**和制作人信息后
        /// 加载页面（Logo页面） END

        /// 主界面（FoxHQ 安装程序）
        private partial Task CreateElement0();
        /// 主界面（FoxHQ 安装程序） END
    }
}
