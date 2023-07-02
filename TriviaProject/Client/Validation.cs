using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Text.RegularExpressions;

namespace Client
{
    public class ValidationUsername : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            try
            {
                string username = value as string;
                Regex letter = new Regex("[a-zA-z]");
                if (username.Length > 12) 
                {
                    return new ValidationResult(false, "username can't be longer than 12");
                }
                if (!letter.IsMatch(username))
                {
                    return new ValidationResult(false, "username must contain a letter");
                }
            }
            catch (Exception ex)
            {
                return new ValidationResult(false, ex.Message);
            }

            return ValidationResult.ValidResult;
        }
    }

    public class ValidationPassword : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            try
            {
                string passwsord = value as string;
                Regex digit = new Regex("[0-9]");
                Regex uppercase = new Regex("[A-Z]");
                Regex lowercase = new Regex("[a-z]");
                Regex specialChar = new Regex("[!@#$%^&*]");

                if (passwsord.Length != 8)
                {
                    return new ValidationResult(false, "password must be 8 chars"); // check if the password lenght is 8
                }
                else if (!digit.IsMatch(passwsord))
                {
                    return new ValidationResult(false, "password must contain digit"); // search lowercase letter
                }
                else if (!uppercase.IsMatch(passwsord))
                {
                    return new ValidationResult(false, "password must contain uppercase letter"); // search uppercase letter
                }
                else if (!lowercase.IsMatch(passwsord))
                {
                    return new ValidationResult(false, "password must contain lowercase letter"); // search digit
                }
                else if (!specialChar.IsMatch(passwsord))
                {
                    return new ValidationResult(false, "password must contain special char"); // search special char
                }
            }
            catch (Exception ex)
            {
                return new ValidationResult(false, ex.Message);
            }

            return ValidationResult.ValidResult;
        }
    }

    public class ValidationEmail : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            try
            {
                string email = value as string;
                Regex emailRegex = new Regex("([A-Za-z0-9]+[._-])*[A-Za-z0-9]+@[A-Za-z0-9-]+(\\.[A-Z|a-z]{2,})+");
                Match match = emailRegex.Match(email);

                if(!match.Success)
                {
                    return new ValidationResult(false, "not in the right format");
                }
                
            }
            catch (Exception ex)
            {
                return new ValidationResult(false, ex.Message);
            }

            return ValidationResult.ValidResult;
        }
    }

    public class ValidationAddress : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            try
            {
                string address = value as string;
                Regex addressRegex = new Regex("([A-Za-z])*[, ]+([0-9])*[, ]+([A-Za-z]+)");
                Match match = addressRegex.Match(address);

                if (!match.Success)
                {
                    return new ValidationResult(false, "not in the right format");
                }

            }
            catch (Exception ex)
            {
                return new ValidationResult(false, ex.Message);
            }

            return ValidationResult.ValidResult;
        }
    }

    public class ValidationPhoneNumber : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            try
            {
                string phone = value as string;
                Regex phoneRegex1 = new Regex("0+([0-9]){8}");
                Regex phoneRegex2 = new Regex("05+([0-9]){8}");
                Match match1 = phoneRegex1.Match(phone);
                Match match2 = phoneRegex2.Match(phone);

                if (!match1.Success || !match2.Success)
                {
                    return new ValidationResult(false, "not in the right format");
                }

            }
            catch (Exception ex)
            {
                return new ValidationResult(false, ex.Message);
            }

            return ValidationResult.ValidResult;
        }
    }

    public class ValidationBirthdate : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            try
            {
                string birthdate = value as string;
                Regex birthdateRegex = new Regex("([0-9]{1,2})\\.([0-9]{1,2})\\.([0-9]{4})");
                Match match = birthdateRegex.Match(birthdate);

                if (!match.Success)
                {
                    return new ValidationResult(false, "not in the right format");
                }

            }
            catch (Exception ex)
            {
                return new ValidationResult(false, ex.Message);
            }

            return ValidationResult.ValidResult;
        }
    }
}
