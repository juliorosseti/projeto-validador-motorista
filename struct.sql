CREATE TABLE `usuario` (
    `id` BIGINT(20) NOT NULL AUTO_INCREMENT,
    `nome` VARCHAR(255) NULL DEFAULT NULL,
    `email` VARCHAR(255) NULL DEFAULT NULL,
    `senha` VARCHAR(255) NULL DEFAULT NULL,
    PRIMARY KEY (`id`)
)
COLLATE='utf8_general_ci'
ENGINE=MyISAM
;

INSERT INTO `usuario` (`id`, `nome`, `email`, `senha`) VALUES (1, 'José Roberto', 'jose@motorista.com.br', '6bdd0496591a1c739dca01d7ac733019');