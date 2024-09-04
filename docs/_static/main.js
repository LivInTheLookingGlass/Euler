$(document).ready( function () {
    document.querySelectorAll('.datatable:not(.centertable)').forEach(function(table) {
        $(table.datable).DataTable({
            paging: false,
            searching: false,
        });
    });

    document.querySelectorAll('.datatable.centertable').forEach(function(table) {
        var tableInstance = $(table.datable).DataTable({
            columnDefs: [{
                targets: '_all',
                orderable: true
            }],
            order: [],
            drawCallback: function() {
                this.api().rows().nodes().to$().each(function(index) {
                    if (index < 6)
                        $(this).addClass('no-sort');
                });
            },
            paging: false,
            searching: false,
        })

        tableInstance.on('order.dt', function() {
            tableInstance.column(0).order('no-sort').draw();
        });

        // Custom sorting behavior
        $.fn.dataTable.ext.order['no-sort'] = function (_, _, dataIndex) {
            if (dataIndex < 6)
                return -1; // Force header and first 5 rows to be at the top
            return 1;
        };
    });
});
