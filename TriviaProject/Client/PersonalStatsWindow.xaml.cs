﻿using System;
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
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for PersonalStatsWindow.xaml
    /// </summary>
    public partial class PersonalStatsWindow : Window
    {
        private Communicator communicator;
        private string username;
        private const int getPersonalStatsRequestCode = 106;
        private const int getPersonalStatsResponseCode = 209;

        public PersonalStatsWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            usernameTextBlock.Text += username;
            getPersonalStats();
        }

        /// <summary>
        /// Gets from the server the personal stats of the user
        /// </summary>
        private void getPersonalStats()
        {
            PacketInfo clientPacket = new PacketInfo() { code=getPersonalStatsRequestCode, data=""};
            communicator.SendPacket(clientPacket);

            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != getPersonalStatsResponseCode)
            {
                MessageBox.Show("Error getting data", "Error", 
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

        }

        /// <summary>
        /// Goes a window back (statistics window)
        /// </summary>
        private void BackClick(object sender, RoutedEventArgs e)
        {
            StatisticsWindow statisticsWindow = new StatisticsWindow(ref communicator, username);
            Close();
            statisticsWindow.ShowDialog();
        }

    }
}
