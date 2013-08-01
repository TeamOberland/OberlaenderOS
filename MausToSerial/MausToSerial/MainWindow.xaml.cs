using System;
using System.IO.Ports;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;
using System.Windows.Input;


namespace MausToSerial
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool _isPortSelected = false;
        private string _portName = "";
        private const int BaudRate = 115200;

        private SerialPort _port;

        public Point WindowMiddle 
        { 
            get
            {
                return new Point((ActualWidth / 2), (ActualHeight / 2));
            } 
        }

        public MainWindow()
        {
            InitializeComponent();
            string[] portList = SerialPort.GetPortNames();
            SerialPortList.Items.Add("No Port");
            foreach (string s in portList)
            {
                SerialPortList.Items.Add(s);
            }
            SerialPortList.SelectedIndex = 0;
        }

        private void SetMousePosition(Point coordinate)
        {
            SetMousePosition((int) coordinate.X, (int) coordinate.Y);
        }

        private void SetMousePosition(int a, int b)
        {
            SetCursorPos(a, b);
        }

        [DllImport("User32.dll")]
        private static extern bool SetCursorPos(int x, int y);

        private void OnPortSelected(object sender, RoutedEventArgs e)
        {
            if (SerialPortList.SelectedIndex == 0) return;
            _isPortSelected = true;
            _portName = (string) SerialPortList.SelectedItem;
            _port = new SerialPort(_portName, BaudRate, Parity.None, 8, StopBits.One);
            _port.Handshake = Handshake.None;
            _port.Open();
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            if (!_isPortSelected) return;

            try
            {
                SendMouseEvent(OnMouseEvent(e, ClickEvent.None));
                Thread.Sleep(25);
            }
            catch (InvalidOperationException ex)
            {
                StopTracking();
                Cooridnate.Content = "Es konnte nichts über diesen Port versendet werden, bitte richtigen Port auswählen";
            }
        }

        private void SendMouseEvent(MouseEvent mouseEvent)
        {
            if (_port == null) return;

            byte[] data = mouseEvent.ToBytes();
            for (int i = 0; i < data.Length; i++)
            {
                _port.Write(new byte[] {data[i]}, 0, 1);
            }
            Thread.Sleep(1000);
        }

        private Point CalculateDifference(Point middleWindow, Point mousePosition)
        {
            return new Point(mousePosition.X - middleWindow.X, mousePosition.Y - middleWindow.Y);
        }

        /// <summary>
        /// Stop the tracking
        /// </summary>
        private void StopTracking()
        {
            _isPortSelected = false;
            SerialPortList.SelectedIndex = 0;
            _portName = "";
            _port.Close();
        }

        private MouseEvent OnMouseEvent(MouseEventArgs e, ClickEvent clickEvent)
        {
            Point mousePosition = e.GetPosition(this);
            Point middlePoint = WindowMiddle;
            Point difference = CalculateDifference(middlePoint, mousePosition);
            difference.X += 8;
            difference.Y += 30;

            Cooridnate.Content = string.Format("WindowPos: {0}|{1}   Middle: {2}|{3}   Diff: {4}|{5}  Click: {6}" , Left, Top,
                                               middlePoint.X, middlePoint.Y, difference.X, difference.Y, clickEvent);

            MouseEvent mEvent = new MouseEvent((int)difference.X, (int)difference.Y, clickEvent);
            SetMousePosition((int)(Left + middlePoint.X), (int)(Top + middlePoint.Y));

            return mEvent;
        }
        
        private void OnMouseLeftDown(object sender, MouseButtonEventArgs e)
        {
            SendMouseEvent(OnMouseEvent(e, ClickEvent.MouseLeftDown));
        }

        private void OnMouseLeftUp(object sender, MouseButtonEventArgs e)
        {
            SendMouseEvent(OnMouseEvent(e, ClickEvent.MouseLeftUp));
        }

        private void OnMouseRightDown(object sender, MouseButtonEventArgs e)
        {
            SendMouseEvent(OnMouseEvent(e, ClickEvent.MouseRightDown));
        }

        private void OnMouseRightUp(object sender, MouseButtonEventArgs e)
        {
            SendMouseEvent(OnMouseEvent(e, ClickEvent.MouseRightUp));
        }

        /// <summary>
        /// Check if the mouse tracking should stop
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                StopTracking();
            }
        }
    }

    /// <summary>
    /// Structure of the MouseEvent
    /// </summary>
    public struct MouseEvent
    {
        public int X;
        public int Y;
        public ClickEvent ClickEvent;

        public MouseEvent(int x, int y, ClickEvent clickEvent)
        {
            X = x;
            Y = y;
            ClickEvent = clickEvent;
        }

        /// <summary>
        /// http://social.msdn.microsoft.com/forums/en-US/csharplanguage/thread/f3ac392a-43e4-4688-83bc-8caffc9a4105
        /// </summary>
        /// <returns></returns>
        public byte[] ToBytes()
        {
            Byte[] bytes = new Byte[Marshal.SizeOf(typeof(MouseEvent))];
            GCHandle pinStructure = GCHandle.Alloc(this, GCHandleType.Pinned);
            try
            {
                Marshal.Copy(pinStructure.AddrOfPinnedObject(), bytes, 0, bytes.Length);
                return bytes;
            }
            finally
            {
                pinStructure.Free();
            }
        }
    }

    /// <summary>
    /// Possible Mouse Events
    /// </summary>
    public enum ClickEvent
    {
        None = 0,
        MouseLeftDown = 1,
        MouseLeftUp = 2,
        MouseRightDown = 3,
        MouseRightUp = 4
    }
}
