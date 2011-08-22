namespace ChelasUIMaker.Engine
{
    public interface IArea<T>
    {
        IArea<T> WithController<C>();

        IArea<T> WithContent<U>(IArea<U> content);
    }
}