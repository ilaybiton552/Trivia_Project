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
    /// Interaction logic for GameResultWindow.xaml
    /// </summary>
    public partial class GameResultWindow : Window
    {
        List<PlayerResult> results;
        public GameResultWindow(List<PlayerResult> results)
        {
            InitializeComponent();
            this.results = results.OrderBy(result => -result.rightAnswers).ToList();
        }

        /// <summary>
        /// Click event, closes the score window
        /// </summary>
        private void ExitClick(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
