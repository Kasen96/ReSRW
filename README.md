# ReSRW

ReSRW 是一个简单又垃圾的性能测试程序，它可以从磁盘上读取数据，对数据进行处理（排序），然后将数据写回磁盘上。更多算法可以自行添加。

# 用法

``` shell
ReSRW (dataset size)(buffer size)(filename)(algorithm mode: qs|ss|is)
```

# 生成文件

1. Dataset: filename.txt
2. Sorted Dataset: filename_result.txt
3. Time result: time_result.txt

# 优化方式

1. 开启 / 关闭编译器优化
2. 选择不同算法
3. 修改缓存大小（理论上）
   * 不知道哪里写错了，居然不会对时间产生影响，佛了...

# LICENSE

               GLWT(Good Luck With That) Public License
                 Copyright (c) Everyone, except Author

Everyone is permitted to copy, distribute, modify, merge, sell, publish,
sublicense or whatever they want with this software but at their OWN RISK.

                            Preamble

The author has absolutely no clue what the code in this project does.
It might just work or not, there is no third option.


                GOOD LUCK WITH THAT PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION, AND MODIFICATION

0. You just DO WHATEVER YOU WANT TO as long as you NEVER LEAVE A
   TRACE TO TRACK THE AUTHOR of the original product to blame for or hold
   responsible.

IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

Good luck and Godspeed.

