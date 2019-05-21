# rb_tree

Реализация словаря на красно-чёрных деревьях.  

Поддерживает указание типов ключа и значения при создании (реализовано через `enum`) для того,  
чтобы самостоятельно определить функции для сравнения ключа, освободения ключа/значения.
Также имеется возможность передать эти функции при создании словаря.  

Одинаковые элементы не сохраняются.
При обращении к несуществующему ранее ключу, он создаётся, а его значение ставится равным  `map->nil`

**Сейчас ft_printf содержится в [libft](https://github.com/liftchampion/libft) - репозиторий существует лишь для демонстации.**

*C код написан в [Norminette code style](https://github.com/liftchampion/Norminette)*
