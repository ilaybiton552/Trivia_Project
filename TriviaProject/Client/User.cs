using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class User
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
        public string address { get; set; }
        public string phone { get; set; }
        public string birthdate { get; set; }

        /// <summary>
        /// the function returns if the object is totally empty
        /// </summary>
        /// <returns>if the object is totally empty</returns>
        public bool isEmpty()
        {
            return (string.IsNullOrEmpty(this.username) || string.IsNullOrEmpty(this.password) || string.IsNullOrEmpty(this.email) || string.IsNullOrEmpty(this.address) || string.IsNullOrEmpty(this.phone) || string.IsNullOrEmpty(this.birthdate));
        }
    }
}
