使用
prenow->link=now->link;
now=prenow->link;
的方法进行循环链表的删除并不完全
最后会剩下一个节点
这时now->link==now;
进行判断 if(now->link==now)
{
    now=NULL;
}