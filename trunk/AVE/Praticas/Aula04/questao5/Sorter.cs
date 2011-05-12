using System;
class Sorter{
 static void Sort<T>(IList<T> l, IComparer<T> cmp){
  //To Do
}
}


class App{
  void printElements(short[] a) {
   //To Do...
   }
  
  static void Main(){
     short[] dummy = {3,4,6,2,1,8,5,9,6,7,0};
     printElements(dummy);
     Sorter.Sort(dummy, new Int16Comparer());
     printElements(dummy);
  }

  class Int16Comparer:IComparer<short>{

  public int Compare(short n1, short n2){
    return (int) n1 – n2;
  }
 }
}