<table class="table table-striped">
    <thead>
        <tr>
            <td><b>Symbol</b></td>
            <!--<td><b>Name</b></td>-->
            <td><b>Shares</b></td>
            <td><b>Price</b></td>
            <td><b>TOTAL</b></td>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <!--<td><?= $position["name"] ?></td>-->
                <td><?= $position["shares"] ?></td>
                <td>$<?= $position["price"] ?></td>
                <td>$<?= $position["profit"] ?></td>
            </tr>
        <?php endforeach ?>
        <tr>
            <td>Your cash</td>
            <td colspan="2"></td>
            <td>$<?= $cash ?></td>
        </tr>
    </tbody>
    <tfoot>
        <tr>
            <td colspan="3"></td>
            <td><b>$<?= $total ?></b></td>
        </tr>
    </tfoot>
</table>