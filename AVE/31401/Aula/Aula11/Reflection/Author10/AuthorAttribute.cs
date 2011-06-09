using System;

namespace Author
{
    //[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property, AllowMultiple = true)]
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property, AllowMultiple = true, Inherited=true)]
    public class AuthorAttribute : Attribute
    {
        private string FamilyName;
        private string GivenName;

        public AuthorAttribute()
        {
            throw new NotImplementedException();
        }
        public AuthorAttribute(string FamilyName)
        {
            this.FamilyName = FamilyName;
        }
        public override String ToString()
        {
            return String.Format("Author: {0} {1}", Family, Given);
        }
        public string Family
        {
            get { return FamilyName; }
            set { FamilyName = value; }
        }
        public string Given
        {
            get
            {
                return GivenName;
            }
            set
            {
                GivenName = value;
            }
        }
    }

}